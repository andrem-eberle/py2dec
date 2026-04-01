#include "common.h"
#include "py_gen.h"
#include "opcodes.h"
#include "disasm.h"
#include "flow.h"

#ifdef LOG_GEN_SOURCE
#define pylog(...) pylog_type("translate",__VA_ARGS__)
#endif

extern char * opcode_name_map[256];

typedef struct f_block_data {
	int st;
	int end;
	int pref;
	earray pblocks;
	f_block_data * fit(int offset) {
		if (offset < st || offset > end) {
			return NULL;
		}
		int i;
		for (i = 0; i < pblocks.size; i++) {
			f_block_data * b = (f_block_data*)earray_get(&pblocks, i, f_block_data*);
			f_block_data * result = b->fit(offset);
			if (result) {
				return result;
			}
		}
		return this;
	}

} f_block_data;

f_block_data * dofit(f_block_data * t, int st, int end) {
	int i;
	for (i = 0; i < t->pblocks.size; i++) {
		f_block_data * b = (f_block_data*)earray_get(&t->pblocks, i, f_block_data*);
		if (b->st < st && b->end < end) {
			return dofit(b,st,end);
		}
	}
	return t;
}

f_block_data * fitblock(py_function * f, int st, int end) {
	int i;
	for (i = 0; i < f->loop_block_data.size; i++) {
		f_block_data * b = (f_block_data*)earray_get(&f->loop_block_data, i, f_block_data*);
		
		if (st > b->st && end < b->end) {
			b = dofit(b, st, end);
			f_block_data * t = new f_block_data();
			t->st = st;
			t->end = end;
			b->pblocks.add(t);
			return t;
		}
	}

	f_block_data * t = new f_block_data();
	t->st = st;
	t->end = end;

	f->loop_block_data.add(t);
	return t;
}

void setblocks(py_function * f) {
	py_instruction * inst = f->instruction_set;
	while (inst < f->instruction_set + f->instruction_set_size) {
		if (inst->opcode == SETUP_LOOP) {
			int st = inst->off;
			int end = inst->loop_data;
			
			f_block_data * b = fitblock(f, st, end);

			py_instruction * inst2 = &f->instruction_set[end];

			while (inst2->opcode != JUMP_ABSOLUTE && inst2->opcode != CONTINUE_LOOP) {
				inst2--;
				
				py_assert(inst2 != f->instruction_set, "Bad loop construct");
			}
			
			b->pref = inst2->to_jmp;
			pylog("loop block between %i and %i, ref at %i", st, end,b->pref);
		}
		inst++;
	}

	inst = f->instruction_set;
	int nested_try_blocks[1024];
	while (inst < f->instruction_set + f->instruction_set_size) {
		if (inst->opcode == SETUP_EXCEPT) {
			int stc = 1;
			int st = inst->off;
			
			nested_try_blocks[stc - 1] = st;
			inst++;
			while (inst < f->instruction_set + f->instruction_set_size) {
				if (inst->opcode == SETUP_EXCEPT) {
					stc++;
					py_assert(stc < 1024, "Too many loops");
					st = inst->off;
					
					nested_try_blocks[stc - 1] = st;
				}
				else if (inst->opcode == END_FINALLY) {
					
					int sst = nested_try_blocks[stc - 1];
					
					f_block_data * b = new f_block_data();
					b->st = sst;
					b->end = inst->off;
					f->try_block_data.add(b);
					pylog("try block between %i and %i", sst, inst->off);
					stc--;
					if (stc == 0) {
						break;
					}
				}
				
				inst++;
			}
			py_assert(stc == 0, "Unbounded except block found");
		}
		inst++;
	}
}

int instructions_same_tryblock(py_function * f, int off1, int off2) {
	int i;
	pylog("check tryblock %i %i", off1, off2);
	f_block_data * b1 = NULL;
	f_block_data * b2 = NULL;
	for (i = 0; i < f->try_block_data.size; i++) {
		f_block_data * b = earray_get(&f->try_block_data, i, f_block_data*);
		if (off1 >= b->st && off1 <= b->end) {
			if (b1) {
				if (b1->st < b->st) {
					b1 = b;
				}
			}
			else {
				b1 = b;
			}
		}
		if (off2>= b->st && off2 <= b->end) {
			if (b2) {
				if (b2->st < b->st) {
					b2 = b;
				}
			}
			else {
				b2 = b;
			}
		}
	}

	if (!b1 || !b2) {
		return 0;
	}
	pylog("b1 %i %i, b2 %i %i", b1->st, b1->end, b2->st, b2->end);
	return (b1 == b2);
}

f_block_data * inloop(py_function *f, int off) {
	int i;
	for (i = 0; i < f->loop_block_data.size; i++) {
		f_block_data * b = (f_block_data*)earray_get(&f->loop_block_data, i, f_block_data*);
		if (off >= b->st && off <= b->end) {
			return b->fit(off);
		}
	}
	return NULL;
}

py_instruction * locate(py_function * f, int offset) {
	int j;
	for (j = 0; j < f->instruction_set_size; j++) {
		if (f->instruction_set[j].off == offset) {
			return &f->instruction_set[j];
		}
	}
	return NULL;
}

void insert_insts(py_function * f, int offset, int size) {
	if (size > (f->instruction_set_fullsize - f->instruction_set_size)) {
		py_instruction * tmp = f->instruction_set;
		f->instruction_set = new py_instruction[f->instruction_set_size * 2];
		memcpy(f->instruction_set, tmp, f->instruction_set_size * sizeof(py_instruction));
		f->instruction_set_size *= 2;
	}

	int i;
	for (i = f->instruction_set_size + size; i > offset; i--) {
		f->instruction_set[i] = f->instruction_set[i - size];
		f->instruction_set[i].off += size;
	}
	f->instruction_set_size += size;
	for (i = 0; i < f->instruction_set_size; i++) {
		if (f->instruction_set[i].to_jmp >= offset ) {
			f->instruction_set[i].to_jmp += size;
		}
		if (f->instruction_set[i].loop_data >= offset) {
			f->instruction_set[i].loop_data += size;
		}
	}

}

int flow_is_reachable(py_function * f, py_instruction *inst) {
	flow_node * n = flow_get_node_from_instruction(f->flow_nodes, inst);
	
	if (!n) {
		return 0;
	}
	if (n->incoming.size == 0) {
		return 0;
	}
	return 1;
}

int translate(py_function * f, py_function * out) {
	pylog("translate start on %s",f->name);
	py_instruction * inst = f->instruction_set;

	*out = *f;
	out->next = NULL;
	int msize = f->instruction_set_size*2;
	out->instruction_set = new py_instruction[msize];
	out->flags |= PY_FUNCTION_FLAG_TRANSLATED;
	int k = 0;
	while (inst < f->instruction_set + f->instruction_set_size) {
		if (k > msize) {
			py_instruction * tmp = out->instruction_set;
			
			out->instruction_set = new py_instruction[msize*2];
			memcpy(out->instruction_set, tmp, msize * sizeof(py_instruction));
			msize *= 2;
		}
		
		out->instruction_set[k] = *inst;
		out->instruction_set[k].off = k;
		out->instruction_set[k].old_off = inst->off;
		out->instruction_set[k].translated = inst;
		out->instruction_set[k].stack_referrals = NULL;
		out->instruction_set[k].stackbacks = NULL;
		out->instruction_set[k].stack_referrals_sz = 0;
		out->instruction_set[k].stackbacks_sz = 0;
		out->instruction_set[k].reverse_stack_referrals = earray();
		inst->translated = &out->instruction_set[k];
		k++;

		
		inst++;
	}
	out->instruction_set_fullsize = msize;
	out->instruction_set_size = k;
	int i;
	for (i = 0; i < f->instruction_set_size; i++) {
		inst = &f->instruction_set[i];
		if (inst->to_jmp >= 0) {
			
			int j;
			py_instruction * p2 = inst->translated;
			py_instruction * ref = locate(f, inst->to_jmp);
			py_assert(ref != NULL, "Invalid translate");
			p2->to_jmp = ref->translated->off;			
			
		}
		if (inst->loop_data) {
			py_instruction * p2 = inst->translated;
			py_instruction * ref = locate(f, inst->loop_data);
			py_assert(ref != NULL, "Invalid translate");
			p2->loop_data = ref->translated->off;
			p2->arg = ref->translated->off;
			
			
		}
		if (inst->opcode == SETUP_WITH) {
			int target = inst->arg + 3 + inst->off;
			py_instruction * ref = locate(f, target);
			inst->translated->arg = ref->translated->off - (inst->translated->off+1);
		}
	}

	pylog("setting blocks");

	setblocks(out);

	pylog("blocks done, loop blocks: %i",out->loop_block_data.size);
	
	if (out->loop_block_data.size > 0) {
		for (i = 0; i < out->instruction_set_size; i++) {
			inst = &out->instruction_set[i];
			if (inst->to_jmp >= 0 && inst->to_jmp < inst->off) {
				f_block_data * loop = inloop(out, inst->off);
				pylog("tojmp %s", inst->highlevel_name);
				if (loop && inst->opcode == POP_JUMP_IF_TRUE || inst->opcode == POP_JUMP_IF_FALSE) {

					f_block_data * targ = inloop(out, inst->to_jmp);
					if (targ == NULL) {
						continue;
					}
					pylog("%i %i %i %llX\n", loop->st, loop->end, inst->to_jmp, targ);
					py_assert(targ == loop, "Unknown translate");

					insert_insts(out, (i), 1);

					strcpy(inst->highlevel_name, opcode_name_map[UNARY_NOT]);
					int old_target = (inst)->to_jmp;
					inst->to_jmp = i + 2;

					if (inst->opcode == POP_JUMP_IF_TRUE) {
						inst->opcode = POP_JUMP_IF_FALSE;
					}
					else {
						inst->opcode = POP_JUMP_IF_TRUE;
					}
					strcpy(inst->highlevel_name, opcode_name_map[inst->opcode]);
					out->instruction_set[i + 1].opcode = CONTINUE_LOOP;
					out->instruction_set[i + 1].to_jmp = old_target;
					out->instruction_set[i + 1].jmp_conditional = 2;
					out->instruction_set[i + 1].arg_ptr = 0;
					out->instruction_set[i + 1].predef_arg = 0;

					out->instruction_set[i + 1].arg = 1;
					strcpy(out->instruction_set[i + 1].highlevel_name, opcode_name_map[CONTINUE_LOOP]);
					set_up_instruction_tos(&out->instruction_set[i + 1]);
					i++;
				}
				else if (loop && inst->opcode == JUMP_ABSOLUTE) {
					py_assert(loop != NULL, "Unknown translate %i", inst->off);
					f_block_data * targ = inloop(out, inst->to_jmp);
					if (targ != loop) {
						pylog("WARNING: back jump outside loop -- %i %s",inst->off, inst->highlevel_name);
						continue;
					}
					py_assert(targ == loop, "Unknown translate %i %s", inst->off,inst->highlevel_name);
					pylog("jump continue %i %i", inst->off, targ->end);
					if (!flow_is_reachable(f, inst->translated) || targ->end == inst->off) {
						pylog("dummy");
						inst->opcode = OPCODE_DUMMY;
					}
					else {
						inst->opcode = CONTINUE_LOOP;
					}
					strcpy(inst->highlevel_name, opcode_name_map[inst->opcode]);
				}
			}

		}
	}

	pylog("translate loops complete");
	for (i = 0; i < out->instruction_set_size; i++) {
		inst = &out->instruction_set[i];
		inst->idx = inst->off;
	}

	py_function * nested_fns = NULL;
	py_function * nested_fns_t = NULL;
	int fn_count = 0;

	py_function * nested_closures = NULL;
	py_function * nested_closures_t = NULL;
	int closure_count;

	py_class * nested_classes = NULL;
	py_class * nested_classes_t = NULL;
	int classes_count = 0;

	py_function * f1 = f->nested_functions;
	while (f1) {
		py_function * pout = new py_function();
		translate(f1, pout);
		f1->translated = pout;
		pout->translated = f1;
		linked_list_insert(nested_fns, nested_fns_t, pout, fn_count);
		f1 = f1->next;
	}

	out->nested_functions = nested_fns;

	f1 = f->nested_closures;
	while (f1) {
		py_function * pout = new py_function();
		translate(f1, pout);
		f1->translated = pout;
		pout->translated = f1;
		
		linked_list_insert(nested_closures, nested_closures_t, pout, closure_count);
		f1 = f1->next;

	}

	out->nested_functions = nested_fns;
	out->nested_closures = nested_closures;

	py_class * cls = f->nested_classes;
	while (cls) {
		py_class* cl1 = new py_class();
		*cl1 = *cls;

		f1 = f->nested_functions;
		py_function * targ = NULL;
		while (f1) {
			if (f1 == cl1->gen_function) {
				targ = f1;
				break;
			}
			f1 = f1->next;
		}
		if (targ == NULL) {
			f1 = f->nested_closures;
			while (f1) {
				if (f1 == cl1->gen_function) {					
					targ = f1;					
					break;
				}
				f1 = f1->next;
			}
		}
		
		py_assert(targ != NULL, "Bad translate");
		py_assert(targ->translated != NULL, "Bad translate");
		
		cl1->gen_function = targ->translated;

		py_function * methods = NULL;
		py_function * methods_t = NULL;
		int methods_sz = 0;
		f1 = cls->methods;
		while (f1) {
			py_assert(f1->translated != NULL, "Invalid translation");
			linked_list_insert(methods, methods_t, f1->translated, methods_sz);
			f1 = f1->next;
		}
		cl1->methods = methods;

		linked_list_insert(nested_classes, nested_classes_t, cl1, classes_count);
		cls = cls->next;
	}
	
	out->nested_classes = nested_classes;
	pylog("translate finished for %s", f->name);
	return 0;
}

#undef pylog
#define pylog(...)