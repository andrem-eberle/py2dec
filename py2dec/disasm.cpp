#include "common.h"
#include "unmarshal.h"
#include "opcodes.h"
#include "flow.h"
#include "stack-solver.h"
#include <assert.h>
#include "disasm.h"

#ifdef LOG_DISASM
#define pylog(...) pylog_type("disasm",__VA_ARGS__)
#endif

extern char * opcode_name_map[];

uint32 PY2_MAGIC_NUMBERS[] = { 50823,60202,60717,62011,62021,62041,62051,62061,62071,62081,62091,62092,62101,62111,62121,62131,62151,62161,62171,62181,62191,62201,62211 };

extern tos_op_data opcode_tos_delta[];

py_instruction dummy;

int disasm_code(byte * data, int sz, un_code * base, py_disasm_context * ctx, py_disasm_output * out, py_function * f);

#define CO_VARARGS	0x0004
#define CO_VARKEYWORDS	0x0008
#define CO_NESTED       0x0010
#define CO_GENERATOR    0x0020

void disasm_process_function(un_code * code, int pdefs, py_instruction * insts, int idx,
	py_function * out, py_disasm_context * ctx) {
	py_instruction * finst = &insts[idx];
	int i;
	int argcount = code->argcount;
	(*out) = py_function();
	out->set_params(argcount);
	
	out->code = code;
	
	if (finst && finst->opcode == MAKE_CLOSURE) {
		py_assert(finst->stack_referrals_sz >= 2, "Invalid CLOSURE found");
		
		py_instruction * pcl = finst->stack_referrals[1];
		
		if (pcl->opcode == BUILD_TUPLE) {	
			un_tuple * t = new un_tuple(pcl->stack_referrals_sz);
			for (i = 0; i < pcl->stack_referrals_sz; i++) {
				py_instruction * fvar = pcl->stack_referrals[i];
				py_assert(fvar->opcode == LOAD_DEREF || fvar->opcode == LOAD_CLOSURE,"Unknown CLOSURE construct");
				py_assert(fvar->arg_ptr != NULL,"Unknown CLOSURE construct, type was %s",fvar->highlevel_name);
				t->data[i] = fvar->arg_ptr;
			}
			out->freevars = t;
		}
		else {
			py_assert(0, "Unknown CLOSURE construct");
		}
	}
			
	for (i = 0; i < (int)code->argcount; i++) {
		out->arg_names[i] = un_resolve_str(code->varnames->data[i]);		
	}

	if (code->flags & CO_VARARGS) {
		// function has varargs		
		out->var_arg = un_resolve_str(code->varnames->data[i]);
		i++;
	}
	if (code->flags & CO_VARKEYWORDS) {
		// function has keywords		
		out->kw_arg = un_resolve_str(code->varnames->data[i]);
		i++;
	}

	strcpy(out->name, (const char*)un_resolve_str(code->name));
	
	un_str * ccode = un_coerce_str(code->code);
	
	py_disasm_output pout;
	
	disasm_code((byte*)ccode->str, ccode->size, code, ctx, &pout,out);

	out->instruction_set = pout.instruction_set;
	out->instruction_set_size = pout.instruction_set_size;

	out->nested_functions = pout.fns;
	out->nested_functions_sz = pout.fns_sz;

	out->nested_closures = pout.closures;
	out->nested_closures_sz = pout.closures_sz;

	out->nested_classes = pout.classes;
	out->nested_classes_sz = pout.classes_sz;

	py_class * cls = pout.classes;
	while (cls) {
		py_function * func = out->nested_functions;
		
		while (func) {
			if (!strcmp(func->name, un_resolve_str(cls->class_name))) {
				func->flags |= PY_FUNCTION_FLAG_CLASSGEN;
				break;
			}
			func = func->next;
		}
		
		cls = cls->next;
	}
	

	out->instruction_by_offset = new py_instruction*[out->instruction_set[out->instruction_set_size-1].off+1];

	for (i = 0; i < out->instruction_set_size - 1; i++) {
		py_instruction * inst = &out->instruction_set[i];
		out->instruction_by_offset[inst->off] = inst;
		inst->idx = i;
	}
}

void disasm_build_function(py_instruction * insts, int idx, py_function * out, py_disasm_context * ctx) {
	
	int pdefs = insts[idx].arg;
	*out = py_function();

	pylog("disasm_build_function, insts is %llX, number of args is %i\n", insts, pdefs);


	un_code * c = un_coerce_code(insts[idx - 1].arg_ptr);
	disasm_process_function(c, pdefs, insts, idx, out, ctx);

}

void dis_build_class(py_instruction * insts, int i, py_class * out_class, py_disasm_context * ctx, 
	py_function * base_fns,py_function * base_closures) {
	pylog("dis_build_class");
	py_class cls;
	py_instruction * cinst = &insts[i];
	
	(*out_class) = py_class();
	py_assert(cinst->stack_referrals_sz == 3, "Unknown class construct");
	py_instruction * gen_inst = cinst->stack_referrals[0];
	py_instruction * make_gen_inst = gen_inst->stack_referrals[0];
	py_assert(gen_inst->opcode == CALL_FUNCTION && (make_gen_inst->opcode == MAKE_FUNCTION || make_gen_inst->opcode == MAKE_CLOSURE),
		"Unknown class construct %s %s",gen_inst->highlevel_name,make_gen_inst->highlevel_name);

	py_assert(make_gen_inst->stack_referrals[0]->opcode == LOAD_CONST, "disasm: Unknown class construct (%i)", insts[i - 3].opcode);
	
	un_code * class_base = un_coerce_code(make_gen_inst->stack_referrals[0]->arg_ptr);
	
	py_instruction * inst_clbasenames = cinst->stack_referrals[1];
	py_assert(inst_clbasenames->opcode == LOAD_CONST || inst_clbasenames->opcode == BUILD_TUPLE,
		"disasm: Unknown class construct (%i)", inst_clbasenames->opcode);
		
	

	py_instruction * inst_clname = cinst->stack_referrals[2];
	
	py_assert(inst_clname->opcode == LOAD_CONST || inst_clname->opcode == LOAD_NAME, "disasm: Unknown class construct (%i %s)", 
		inst_clname->opcode, inst_clname->highlevel_name);
	
	out_class->class_name = un_reduce_str(inst_clname->arg_ptr);
	
	out_class->generator_function = class_base;
	out_class->inst = cinst;

	
	un_str * ccode = un_coerce_str(class_base->code);
	py_disasm_output pout;

	py_function * f = base_fns;

	while (f) {
		if (f->code == class_base)	{		
			break;
		}
		f = f->next;
	}
	
	
	if (!f) {
		f = base_closures;
		while (f) {
			if (f->code == class_base) {
				break;
			}
			f = f->next;
		}
	}
	py_assert(f != NULL, "Could not locate class build function");
	out_class->gen_function = f;
	//disasm_code((byte*)ccode->str, ccode->size, class_base, ctx, &pout,f);
	out_class->instruction_set = pout.instruction_set;
	out_class->instruction_set_size = pout.instruction_set_size;

	out_class->methods = f->nested_functions;
	out_class->methods_sz = f->nested_functions_sz;	

	return;	


}

#define is_opcode_NAME(o) ((o) == LOAD_NAME || (o) == STORE_NAME || (o) == IMPORT_NAME || (o) == LOAD_ATTR)

void set_up_instruction_tos(py_instruction * inst) {
	uint32 dval = opcode_tos_delta[inst->opcode].added;
	if (dval & OPCODE_TOS_ARG) {
		dval = (dval & 0x0FFFFFFF);
		dval += inst->arg;
	}
	else if (dval & OPCODE_TOS_ARG2) {

		dval = (dval & 0x0FFFFFFF);
		uint32 d1 = inst->arg & 0xF;
		uint32 d2 = inst->arg >> 8;
		dval += (d1 + 2 * d2);
	}

	inst->tos_op_in = dval;
	dval = opcode_tos_delta[inst->opcode].removed;
	if (dval & OPCODE_TOS_ARG) {
		dval = (dval & 0x0FFFFFFF);
		dval += inst->arg;
	}
	else if (dval & OPCODE_TOS_ARG2) {

		dval = (dval & 0x0FFFFFFF);
		uint32 d1 = inst->arg & 0xF;
		uint32 d2 = inst->arg >> 8;
		dval += (d1 + 2 * d2);
	}
	inst->tos_op_out = dval;

	inst->tos_op_peek = opcode_tos_delta[inst->opcode].peeked;
}

int disasm_code(byte * data, int sz, un_code * base, py_disasm_context * ctx,py_disasm_output * dout, py_function * local_function) {
	pylog("disasm_code %s",local_function->name);
	byte * t = data;
	py_instruction inst;

	py_function * nested_fns = NULL;
	py_function * nested_fns_t = NULL;
	int fn_count = 0;

	py_function * nested_closures = NULL;
	py_function * nested_closures_t = NULL;
	int closure_count;

	py_class * nested_classes = NULL;
	py_class * nested_classes_t = NULL;
	int classes_count = 0;

	py_instruction * insts;
	int inst_sz = 1;
	insts = (py_instruction *)calloc(inst_sz, sizeof(py_instruction));	
	
	un_str * linenos;
	if (((un_type*)base->lnotab)->type == TYPE_STRING) {
		linenos = un_coerce_str(base->lnotab);
	}
	else if (((un_type*)base->lnotab)->type == TYPE_STRINGREF) {
		linenos = un_resolve_strref(base->lnotab);
	}
	
	int i = 0;	
	
	while (t < data + sz) {
		int skip = 0;
		inst.opcode = *t;
		t++;
		inst.has_arg = 0;
		inst.predef_arg = 0;
		inst.off = (int)((t-1) - data);
		inst.line_no = 0;
		char * tl = linenos->str;
		// search for line no, based on lnotab_notes.txt in Python2 source
		int off = 0;
		int lineno = 1;
		while (tl < linenos->str + linenos->size) {
			
			off += *tl;
			if (off > inst.off) {
				inst.line_no = lineno;
				
				break;
			}
			lineno += *(tl + 1);
			tl += 2;
		}
		if (!inst.line_no) {
			inst.line_no = lineno;
		}
		py_assert(inst.line_no, "Line number not found for opcode (%i)",inst.off);

		py_assert(opcode_name_map[inst.opcode] != 0, "Bad opcode");
		strcpy(inst.highlevel_name, opcode_name_map[inst.opcode]);
		
		if (inst.opcode >= HAVE_ARGUMENT) {			
			inst.has_arg = 1;
			inst.arg = *(uint16*)t;
		}

		set_up_instruction_tos(&inst);
				
		
		if (!skip) {
			if (inst.has_arg) {
				t += 2;
			}
			if (i >= inst_sz) {
				py_instruction * old = insts;
				inst_sz *= 2;
				insts = (py_instruction *)calloc(inst_sz, sizeof(py_instruction));
				memcpy(insts, old, i * sizeof(py_instruction));
				free(old);
			}

			insts[i++] = inst;
		}		
	}
	
	un_tuple * tconsts = (un_tuple*)base->consts;

	int n = i;
	int jmp_fill = 0;
	for (i = 0; i < n; i++) {
		
		if (insts[i].has_arg) {
			if (insts[i].opcode == LOAD_CONST) {	
				insts[i].arg_ptr = tconsts->data[insts[i].arg];
				insts[i].predef_arg = 1;
				insts[i].stack_op = 1;
			}		
			if (insts[i].opcode == LOAD_GLOBAL) {
				insts[i].stack_op = 1;
				insts[i].predef_arg = 1;
				insts[i].arg_ptr = base->names->data[insts[i].arg];
			}
			if (insts[i].opcode == LOAD_FAST) {
				insts[i].stack_op = 1;
				insts[i].predef_arg = 1;
				
				insts[i].arg_ptr = base->varnames->data[insts[i].arg];

			}
			if (insts[i].opcode == LOAD_DEREF || insts[i].opcode == LOAD_CLOSURE) {
				insts[i].stack_op = 1;
				insts[i].predef_arg = 1;
				if (base->cellvars->size > insts[i].arg) {
					insts[i].arg_ptr = base->cellvars->data[insts[i].arg];
				}
				else {
					int idx = insts[i].arg - base->cellvars->size;
					py_assert(base->cellvars->size > idx || local_function->freevars->size >idx, "Invalid cellvars reference");
					if (base->freevars->size > idx) {
						insts[i].arg_ptr = base->freevars->data[idx];
					}
					else if (local_function->freevars && local_function->freevars->size > idx) {
						insts[i].arg_ptr = base->freevars->data[idx];
					}
					else {
						py_assert(0,"Invalid LOAD_CLOSURE");
					}
				}
				
				py_assert(insts[i].arg_ptr != NULL, "Invalid LOAD_CLOSURE");
				
			}			
			else if (insts[i].opcode ==  SETUP_WITH) {
				
			}
			
			else if (insts[i].opcode == JUMP_ABSOLUTE) {
				insts[i].jmp_conditional = 0;
				insts[i].to_jmp = insts[i].arg;
				if (insts[i].to_jmp < insts[i].off) {
					insts[i].jmp_conditional = 2;
				}
			}
			else if (insts[i].opcode == JUMP_FORWARD) {
				insts[i].jmp_conditional = 0;
				insts[i].to_jmp = insts[i].off + 3 + insts[i].arg;
			}
			else if (insts[i].opcode == POP_JUMP_IF_FALSE || insts[i].opcode == POP_JUMP_IF_TRUE) {
				insts[i].jmp_conditional = 1;
				insts[i].to_jmp = insts[i].arg;
			}
			else if (insts[i].opcode == JUMP_IF_FALSE_OR_POP) {
				insts[i].jmp_conditional = 1;
				insts[i].to_jmp = insts[i].arg;
			}			
			else if (insts[i].opcode == FOR_ITER) {
				insts[i].jmp_conditional = 1;				
				insts[i].to_jmp = insts[i].off + 3 + insts[i].arg;
			}			
			else if (insts[i].opcode == SETUP_EXCEPT) {
				insts[i].jmp_conditional = 1;
				insts[i].to_jmp = insts[i].off + 3 + insts[i].arg;
			}			
			else if (insts[i].opcode == SETUP_FINALLY) {
				insts[i].jmp_conditional = 1;
				insts[i].to_jmp = insts[i].off + 3 + insts[i].arg;
			}
			else if (insts[i].opcode == SETUP_LOOP) {
				insts[i].loop_data = insts[i].off + 3 + insts[i].arg;
			}
			else if (insts[i].opcode == IMPORT_FROM) {
				insts[i].arg_ptr = base->names->data[insts[i].arg];
				insts[i].predef_arg = 1;
			}
			else if (insts[i].opcode == STORE_ATTR) {
				insts[i].arg_ptr = base->names->data[insts[i].arg];
				insts[i].predef_arg = 1;
			}
			else if (insts[i].opcode == STORE_GLOBAL) {
				insts[i].arg_ptr = base->names->data[insts[i].arg];
				insts[i].predef_arg = 1;
			}
			if (insts[i].opcode == STORE_DEREF) {
				insts[i].predef_arg = 1;
				if (base->cellvars->size > insts[i].arg) {
					insts[i].arg_ptr = base->cellvars->data[insts[i].arg];
				}
				else {
					int idx = insts[i].arg - base->cellvars->size;
					py_assert(base->cellvars->size > idx, "Invalid cellvars reference");
					insts[i].arg_ptr = base->freevars->data[insts[i].arg];
				}			
			}
			
			else if (insts[i].opcode == STORE_FAST) {
				insts[i].arg_ptr = base->varnames->data[insts[i].arg];
				insts[i].predef_arg = 1;
			}
			else if (is_opcode_NAME(insts[i].opcode)) {
				insts[i].arg_ptr = base->names->data[insts[i].arg];
				insts[i].predef_arg = 1;
			}		
			
		}
		else {

			if (insts[i].opcode == RETURN_VALUE) {
				if (i < (n - 1)) {
					// we do a fake jump here for the next node
					insts[i].jmp_conditional = 0;
					insts[i].to_jmp = insts[i + 1].off;
				}
				else {
					insts[i].eob = 1;
				}
			}
			else if (insts[i].opcode == BREAK_LOOP) {
				insts[i].brk = 1;
				insts[i].jmp_conditional = 2;
			}
			else if (insts[i].opcode == END_FINALLY) {
				insts[i].to_jmp = insts[i].off + 1;
				
			}

		}
	}

	local_function->instruction_set = insts;
	local_function->instruction_set_size = n;

	local_function->flow_nodes = new flow_graph();
	
	build_flow(insts, n,local_function->flow_nodes,local_function->name);
	//top_down_solver(&local_function->flow_nodes->nodes, local_function);
	top_down_solver2( local_function);
	pylog("solver ended");
	for (i = 0; i < n; i++) {	
		if (insts[i].opcode == BUILD_CLASS) {	
			py_class * cls = new py_class();

			dis_build_class(insts, i, cls, ctx, nested_fns,nested_closures);
			cls->idx = i;
			linked_list_insert(nested_classes, nested_classes_t, cls, classes_count);

		}
		else if (insts[i].opcode == MAKE_FUNCTION || insts[i].opcode == MAKE_CLOSURE) {
			py_function * pfunc = new py_function();
			disasm_build_function(insts, i, pfunc, ctx);
			pfunc->idx = i;
			if (insts[i].opcode == MAKE_FUNCTION) {
				pylog("add nested function %s", pfunc->name);
				linked_list_insert(nested_fns, nested_fns_t, pfunc, fn_count);
			}
			else {
				linked_list_insert(nested_closures, nested_closures_t, pfunc, closure_count);
			}

		}
	}
	
	dout->instruction_set = insts;
	dout->instruction_set_size = n;

	dout->fns = nested_fns;	
	dout->fns_sz = fn_count;

	dout->closures = nested_closures;
	dout->closures_sz = closure_count;

	dout->classes = nested_classes;
	dout->classes_sz = classes_count;
	pylog("disasm_code ended");
	
	return 0;
}

un_tuple * disasm_build_unpacked_tuple_arg(py_instruction * next) {
	py_assert(next->opcode == UNPACK_SEQUENCE,"Unknown default arg tuple unpack %s", next->highlevel_name);
	int size = next->arg;
	un_tuple * tuple = new un_tuple(size);
	
	int i;
	for (i = 0; i < size; i++) {
		py_instruction * ni = earray_get(&next->reverse_stack_referrals, i, py_instruction*);
		if (ni->opcode == STORE_FAST) {
			tuple->data[i] = ni->arg_ptr;
		}
		else if (ni->opcode == UNPACK_SEQUENCE) {
			tuple->data[i] = disasm_build_unpacked_tuple_arg(ni);
		}
		else {
			py_assert(0, "Unknown default arg tuple unpack %s", next->highlevel_name);
		}
	}		
		
	return tuple;
}

un_tuple * disasm_build_unpacked_tuple(py_instruction * inst, py_function * base) {
	py_assert(inst->opcode == LOAD_FAST, "Unknown default arg tuple unpack %s", inst->highlevel_name);
	py_assert(inst->reverse_stack_referrals.size > 0, "Unsolved default arg tuple unpack");
	py_instruction * stunpack = earray_get(&inst->reverse_stack_referrals, 0, py_instruction*);
	return disasm_build_unpacked_tuple_arg(stunpack);
	
}

void disasm_print_function(FILE * fp,py_function * pout, char * type) {
	int i;
	char tmp[20148];
	
//	py_assert(pout->flags&PY_FUNCTION_FLAG_TRANSLATED, "Bad function %s", pout->name);
	
	disasm_pretty_print_function(tmp, pout);
	fprintf(fp, "%s %s:\n",type, tmp);
	fprintf(fp, "\n");
	
	disasm_print_instructions(fp, pout->instruction_set, pout->instruction_set_size);
	
	
	py_function *nested = pout->nested_functions;
	while (nested) {
	
		if (!(nested->flags & PY_FUNCTION_FLAG_CLASSGEN)) {
			disasm_print_function(fp, nested,"function");
		}
		nested = nested->next;
	}

	nested = pout->nested_closures;
	
	while (nested) {
		disasm_print_function(fp, nested, "closure");		
		nested = nested->next;
	}

	py_class * nclass = pout->nested_classes;
	while(nclass) {

		fprintf(fp, "class %s:\n", un_resolve_str(nclass->class_name));
		fprintf(fp, "\n");
		py_assert(nclass->gen_function != NULL, "Bad class gen function");
		disasm_print_function(fp, nclass->gen_function, "build class function");
		
		py_function * method = nclass->methods;
		int j;
		for (j = 0; j < nclass->methods_sz; j++) {			
			disasm_print_function(fp, method, "method");			
			method = method->next;
		}

		nclass = nclass->next;
		fprintf(fp, "\n");
	}
}

void disasm_print_all(py_function * pout) {
	char tmp[2048];
	int i;
	
	FILE * fp = fopen(global_config.output_asm_file, "wb");
	
	disasm_print_function(fp, pout, "function");
	fclose(fp);
}

int disasm_process(byte * data, int sz, py_function * pout) {
	dummy.opcode = OPCODE_DUMMY;
	uint32 magic = *(uint16*)data;
	int i;

	int f = 0;
	for (i = 0; i < sizeof(PY2_MAGIC_NUMBERS) / sizeof(uint32); i++) {
		
		if (magic == PY2_MAGIC_NUMBERS[i]) {
			f = 1;
			break;
		}
	}
	

	if (!f) {
		printf("Bad magic number: %X. Only Python 2.7 supported for now\n", magic);
		return -1;
	}

	byte * t = data + 4;

	uint32 ts = *(uint32*)t;

	t += 4;
	un_type * out;
	printf("Starting unmarshal...\n");
	
	int rt = unmarshal_from_bytes(t, sz - 8,&out);
	if (rt < 0) {
		return -1;
	}	

	py_assert((out->type == TYPE_CODE), "Invalid object");
	
	un_code * code = (un_code*)out;
	un_str * ccode = (un_str*)code->code;
	
	py_assert((ccode->type.type == TYPE_STRING),"Code object is not string");
	
	py_disasm_context context = py_disasm_context();
	
	printf("Disassembling...\n");
	disasm_process_function(code, 0, NULL, 0, pout, &context);
	pylog("disassemble ended");

	
	pylog("disasm print ");
	return 0;

}


/* pretty print functions */

void disasm_print_instructions(FILE * fp, py_instruction * instruction_set,int instruction_set_size) {
	int j;
	int lastline = -1;
	
	for (j = 0; j < instruction_set_size; j++) {
		py_instruction * inst = &instruction_set[j];
		char tmp[4096];
		
		disasm_pretty_print(tmp, inst, lastline);

		lastline = instruction_set[j].line_no;
		fprintf(fp, "%s\n", tmp);
	}
	fprintf(fp, "\n");
}

char * disasm_pretty_print_function(char * out, py_function * function) {
	char * t = out;
	sprintf(t, "%s(", function->name);
	t += strlen(t);

	int i;
	for (i = 0; i < function->argcount; i++) {
		sprintf(t, "%s,", function->arg_names[i]);
		t += strlen(t);
	}
	
	if (function->var_arg) {
		sprintf(t, "*%s,", function->var_arg);
		t += strlen(t);
	}

	if (function->kw_arg) {
		sprintf(t, "**%s,", function->kw_arg);
		t += strlen(t);
	}
	if (*(t-1) == ',') t--;

	sprintf(t, ")");
	return out;
}


char * disasm_pretty_print(char * out, py_instruction * inst, int refline) {
	char tmp[8192];
	char * t = out;
	if (refline != inst->line_no) {
		int line_len = num_len(inst->line_no);
		sprintf(t, " L.");
		t+=3;
		int i;
		for (i = 0; i < 3 - line_len; i++) {
			*t++ = ' ';
		}
		sprintf(t, "%i  ", inst->line_no);
		t += strlen(t);
	}
	else {
		sprintf(t, "        ");
		t += strlen("        ");
	}

	t = right_sprint_num(t, inst->off, 5);
	

	if (inst->predef_arg) {
		sprintf(t, " %s %s",inst->highlevel_name,un_dump_object(tmp, inst->arg_ptr));
	}
	else if (inst->has_arg) {
		sprintf(t, " %s %i", inst->highlevel_name, inst->arg);
	}
	else {		
		sprintf(t, " %s", inst->highlevel_name );
	}
	t += strlen(t);

	if (inst->to_jmp > -1) {
		sprintf(t, " to %i", inst->to_jmp);
	}
	return out;
}

#undef pylog
#define pylog(...)