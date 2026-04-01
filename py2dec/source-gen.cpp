#include "source-gen.h"
#include "limits.h"
#include "opcodes.h"
#include "unmarshal.h"
#include "py_gen.h"
#include "source-util.h"
#include "translate.h"

#ifdef LOG_GEN_SOURCE
#define pylog(...) pylog_type("source-gen",__VA_ARGS__)
#endif

#define ATOM_FLAG_LARGE_STORAGE		0x1
#define ATOM_FLAG_LOOP_START		0x2
#define ATOM_FLAG_COND_ELSE			0x4
#define ATOM_FLAG_BREAK_LINE		0x8
#define ATOM_FLAG_FINALLY_BLOCK		0x10
#define ATOM_FLAG_EXCEPT_BLOCK		0x20
#define ATOM_FLAG_TRY_BLOCK			0x40
#define ATOM_FLAG_DELEGATE			0x80
#define ATOM_FLAG_MULTISTACK		0x100

struct source_atom_tree_node;
struct source_atom;

typedef struct source_atom_callfunction source_atom_callfunction;

typedef struct generic_queue {
	void * data;
	generic_queue * next;
	generic_queue() {
		next = NULL;
	}
} generic_queue;

typedef struct source_atom_tree_node {
	source_atom_tree_node * parent;

	source_atom_tree_node * children_head;
	source_atom_tree_node * children_tail;
	source_atom_tree_node * next;
	source_atom_tree_node * prev;

	source_atom * atom;

	source_atom_tree_node() {
		memset(this,0,sizeof(source_atom_tree_node));
	}

	source_atom * get_tree_top() {
		source_atom_tree_node * p = this;
		while (p->parent) {
			p = p->parent;
		}
		return p->atom;
	}

	source_atom_tree_node * get_tree_top_ref() {
		source_atom_tree_node * p = this;
		while (p->parent) {
			p = p->parent;
		}
		return p;
	}

	
	void add_child(source_atom_tree_node * at) {
		at->parent = this;
		at->next = NULL;
		at->prev = NULL;
		if (children_tail) {
			children_tail->next = at;
			at->prev = children_tail;
		}
		else {			
			children_head = at;
		}
		children_tail = at;
	}

} source_atom_tree_node;

struct source_atom;

#define WATERMARK 0xabcd1299

typedef struct source_atom_data {
	uint32 watermark;
	source_atom *(*replace_dest_atom)(void * st,struct source_atom * at,int index);

	void init() {
		watermark = WATERMARK;
	}
} source_atom_data;

typedef struct source_atom {
	int len;
	int idx;
	int type;

	int depth;
	int tos_op_in;
	int tos_op_out;

	int except_base;
	int start;
	int flags;
	flow_node * ref_node;

	void * data;

	py_instruction * inst;

	earray referenced_nodes;

	source_atom() {
		memset(this, 0, sizeof(source_atom));
		depth = -1;
	}

	int get_top_all_branches(source_atom_tree_node ** out) {
		source_atom_tree_node * p = earray_get(&referenced_nodes, 0, source_atom_tree_node*);
		
		generic_queue * q = new generic_queue();
		generic_queue * qt = q;
		int i;
		q->data = p;
		int k = 0;

		while (q) {
			source_atom_tree_node * n = (source_atom_tree_node*)q->data;
			generic_queue * t = q;
			q = q->next;
			delete t;
			if (!q) qt = NULL;
			
			if (!n->parent) {
				py_assert(k < 128, "Too many atoms on branching?");
				out[k++] = n;
			}
			else {
				for (i = 0; i < n->atom->referenced_nodes.size; i++) {
					source_atom_tree_node * n1 = earray_get(&n->atom->referenced_nodes, i, source_atom_tree_node*);
					t = new generic_queue();
					py_assert(n1->parent != NULL, "Invalid atom construct");
					t->data = n1->parent;
			
					if (qt) {
						qt->next = t;
					}
					else {
						q = t;
					}
					qt = t;
				}
			}
		}
		return k;
		
	}

	source_atom * get_tree_top() {
		//py_assert(referenced_nodes.size == 1, "Unknown overlap on node struct");
		source_atom_tree_node * n = earray_get(&referenced_nodes, 0, source_atom_tree_node*);
		return n->get_tree_top();
	}

	source_atom_tree_node * get_tree_top_ref() {
		source_atom_tree_node * n = earray_get(&referenced_nodes, 0, source_atom_tree_node*);
		return n->get_tree_top_ref();
	}

} source_atom;

typedef struct source_atom_tree {
	int ninsts;
	source_atom_tree_node * root_head;
	source_atom_tree_node * root_tail;
	source_atom * storage;
	source_atom except_placeholder;
	earray extra_atoms;
	int idx;

	source_atom_callfunction * caller;
	source_atom_tree * caller_atoms;

	source_atom_tree(int isize) {
		memset(this, 0, sizeof(source_atom_tree));
		ninsts = isize;
		storage = new source_atom[ninsts];
		except_placeholder.len = 1;
		
		
	}

	source_atom * get_except_placeholder() {
		return &except_placeholder;
	}

	void insert_before(source_atom * before, source_atom * atom) {
		source_atom_tree_node * node = new source_atom_tree_node();
		node->atom = atom;
		atom->referenced_nodes.add_unique(node);

		source_atom_tree_node * t = root_head;
		while(t) {
			if (t->atom == before) {
				
				if (t->prev) {
					t->prev->next = node;					
				}
				else {
					root_head = node;
				}
				node->next = t;
				node->prev = t->prev; 
				t->prev = node;
				
				return;
			}
			t = t->next;
		}
		py_assert(0,"Insert before not found");
	}

	source_atom * extra_atom() {
		source_atom * ex = new source_atom();
		ex->idx = idx;
		idx++;
		extra_atoms.add(ex);
		return ex;
	}

	void add_root_node(source_atom * at) {
		
		source_atom_tree_node * node = new source_atom_tree_node();
		node->atom = at;
		at->referenced_nodes.add_unique(node);
		if (!root_head) {
			root_head = node;			
		}
		else {
			root_tail->next = node;
			node->prev = root_tail;
		}
		root_tail = node;
		
	}

	source_atom_tree_node * get_root_node(source_atom * at) {
		source_atom_tree_node * n = root_head;
		while(n) {
			if (n->atom == at) {
				return n;
			}
			n = n->next;
		}
		return NULL;
	}

	source_atom_tree_node * node_root_swap(source_atom * at, source_atom * parent) {
		
		source_atom_tree_node * n1 = get_root_node(at);
		if (at == parent) {
			return n1;
		}
		source_atom_tree_node * n2 = get_root_node(parent);
		//pylog("root swap %i %i", at->type,at->inst ? at->inst->off : -1);
		py_assert(n2 != NULL,"Bad parent node on swap");
		
		if (!n1) {
			n1 = new source_atom_tree_node();
			n1->atom = at;
			at->referenced_nodes.add_unique(n1);
		}
		
		parent->flags |= at->flags;		
		
		parent->depth = at->depth;
		n1->parent = n2;
		source_atom_tree_node * old_next = n1->next;
		source_atom_tree_node * old_prev = n1->prev;
				
		n2->add_child(n1);

		if (old_next) {
			old_next->prev = old_prev;
		}
		if (old_prev) {
			old_prev->next = old_next;
		}
		if (root_head == n1) {
			root_head = old_next;
		}
		if (root_tail == n1) {
			root_tail = old_prev;
		}

		return n2;
		
	}

	source_atom * from_instruction(py_instruction * inst) {
		py_assert(inst->off >= 0 && inst->off < ninsts,"Bad instruction offset");
		
		return &storage[inst->off];
	}

	source_atom * from_off(int off) {
		return &storage[off];
	}	

} source_atom_tree;


typedef struct source_import_name {
	char symbol[256];
	source_atom * fromlist;
	source_atom * length;
} source_import_name;

#define SOURCE_BINARY_NO_PARENTHESIS 1

source_atom * binary_op_replace_dest_atom(void * st, source_atom * at, int index);

typedef struct source_binary_op {
	source_atom_data pdata;
	source_atom * op1;
	source_atom * op2;
	int type;
	int flags;
	source_binary_op() {
		memset(this, 0, sizeof(source_binary_op));
		pdata.init();
		pdata.replace_dest_atom = binary_op_replace_dest_atom;
	}
} source_binary_op;

source_atom * binary_op_replace_dest_atom(void * st, source_atom * at, int index) {
	source_binary_op * b = (source_binary_op*)st;
	py_assert(index < 2, "Invalid index replace on binary ops");
	source_atom * old;
	
	if (index == 0) {
		old = b->op1;
		b->op1 = at;
	}
	else {
		old = b->op2;
		b->op2 = at;
	}
	return old;
}

typedef struct source_inplace_op {
	source_atom * op1;
	source_atom * op2;
	int type;
} source_inplace_op;



typedef struct source_atom_buildset {
	int size;
	earray data;
	source_atom_buildset() {
		size = 0;
		memset(this, 0, sizeof(source_atom_buildset));
	}
	
	void add_key_pair(source_atom * key, source_atom * value) {
		data.add(key);
		data.add(value);
		size++;
	}

} source_atom_buildset;

typedef struct source_atom_list {
	int size;
	int type;
	int flags;
	source_atom ** elems;
	source_atom_list() {
		memset(this, 0, sizeof(source_atom_list));
	}
} source_atom_list;



typedef struct source_atom_generator_construct {
	source_atom * expr;

} source_atom_generator_construct;

#define SOURCE_ATOM_FLAG_INLINEFOR_ARG0 1



typedef struct source_atom_inline_for_construct {
	source_atom ** var;
	int var_size;
	source_atom * finalfunction;
	source_atom * function;
	source_atom * storage;
	source_atom * pexec;
	source_atom * opt_op;
	
	
	int flags;
	earray conditionals;
	source_atom_inline_for_construct() {
		memset(this, 0, sizeof(source_atom_inline_for_construct));
	}
} source_atom_for_lambda_construct;

typedef struct source_atom_unpacked_sequence {
	source_atom * rt;
	int used;
	int size;
} source_atom_unpacked_sequence;

typedef struct source_atom_with {
	source_atom * expr;
	source_atom * origin;	
	py_instruction * with;
} source_atom_with;

#define SOURCE_ATOM_OPS_OPONLY 1

typedef struct source_atoms_ops {
	source_atom * param1;
	source_atom * param2;
	int op;
	int flags;
	source_atoms_ops() {
		memset(this, 0, sizeof(source_atoms_ops));
	}
} source_atoms_ops;

typedef struct source_atom_raise {
	source_atom * params[3];	
	int size;
} source_atom_raise;

typedef struct source_atoms_slice {
	source_atom * params[3];
	source_atom * origin;
	int size;	
} source_atoms_slice;

#define SLICE_FLAG_NO_RIGHTHAND 1

typedef struct source_atoms_delete_slice {
	source_atom * params[3];
	source_atom * st;
	int type;
} source_atoms_delete_slice;

typedef struct source_atoms_store_slice {
	source_atom * params[3];
	source_atom * st;
	source_atom * dest;
	int flags;
	int type;
	source_atoms_store_slice() {
		memset(this, 0, sizeof(source_atoms_store_slice));
	}
} source_atoms_store_slice;

typedef struct source_atom_class {
	un_code * c;
	source_atom *params[3];
	py_class * cls;
	source_atom * basefn;
	source_atom * baseclnames;
} source_atom_class;

typedef struct source_atom_compare {
	int op;
	int len;
	source_atom ** params;
} source_atom_compare;

typedef struct source_atom_keyval {
	source_atom * key;
	source_atom * value;
} source_atom_keyval;

typedef struct source_atom_str {
	int type;
	int subtype;
	int size;
	char * bytes;
} source_atom_str;

#define ATOM_TUPLE_FLAG_NO_PARENTHESIS 1

typedef struct source_atom_tupleconst {
	un_tuple * tuple;
	int flags;
	source_atom_tupleconst() {
		flags = 0;
	}
} source_atom_tupleconst;

#define SOURCE_FUNCTION_FLAG_SPECIAL_CLASS		0x1
#define SOURCE_FUNCTION_FLAG_LAMBDA				0x2
#define SOURCE_FUNCTION_FLAG_NESTED_DECORATOR	0x4
#define SOURCE_FUNCTION_FLAG_GENERATOR			0x8
#define SOURCE_FUNCTION_FLAG_SETCOMP			0x10
#define SOURCE_FUNCTION_FLAG_DICTCOMP			0x20

typedef struct source_atom_function  {
	int defargs_sz;
	source_atom ** defargs;
	char * fnname;
	un_code * code;	
	py_function * func;
	char annotation[256];
	int flags;
	
	source_atom_function() {
		memset(this, 0, sizeof(source_atom_function));
	}
} source_atom_function;

typedef struct source_atom_callfunction  {
	source_atom * fn;
	int varg_count;
	int kwarg_count;
	int flags;
	source_atom ** vargs;
	source_atom ** kwargs;

	source_atom * va;
	source_atom * kw;
	
	source_atom_callfunction() {
		memset(this, 0, sizeof(source_atom_callfunction));
	}
} source_atom_callfunction;


typedef struct source_atom_int {
	int64 val;
} source_atom_int;

typedef struct source_atom_int64 {
	int64 val;
} source_atom_int64;

source_atom * store_val_replace_dest_atom(void * st, source_atom * at, int index);

typedef struct source_atom_store_val {
	source_atom_data pdata;
	source_atom * st_atom;
	char * var;
	source_atom_generator_construct * generator;
	source_atom_store_val() {
		memset(this, 0, sizeof(source_atom_store_val));
		pdata.init();
		pdata.replace_dest_atom = store_val_replace_dest_atom;		
	}	

} source_atom_store_val;

source_atom * store_val_replace_dest_atom(void * st, source_atom * at, int index) {
	source_atom_store_val * sst = (source_atom_store_val*)st;
	source_atom * old = sst->st_atom;
	sst->st_atom = at;
	return old;
}

typedef struct source_atom_store_attr {
	source_atom * st_atom;
	char * var;
	source_atom * obj;
} source_atom_store_attr;


typedef struct source_atom_store_subscr_val {
	source_atom * st_atom;
	source_atom * var;
	source_atom * subscr;

} source_atom_store_subscr_val;

typedef struct source_atom_loadattr {
	source_atom * ref_atom;
	source_atom_str attr;
} source_atom_loadattr;

void gen_print_atom(source_atom * atom, source_gen_out_buf * out, source_atom_tree * atoms);
void gen_source_obj(py_function * fn, int idx, source_atom_tree * atoms, source_atom * out);
void gen_build_list(int type, py_function * fn, int idx, source_atom_tree * atoms, source_atom * out);
void gen_print_source(py_function * fn, source_gen_out_buf * fout, int base_depth);


int gen_get_inst_start_ref(py_function * fn, int idx, source_atom_tree * atoms);
void gen_print_atom_structure(py_function * fn, source_atom * atom);
void gen_prepare_function(py_function * fn);


enum SOURCE_TYPES {
	SOURCE_ATOM_LIST = 1,
	SOURCE_ATOM_INT,
	SOURCE_ATOM_STR,
	SOURCE_ATOM_TUPLE,
	SOURCE_ATOM_STORE_VAR,
	SOURCE_ATOM_FUNCTION,
	SOURCE_ATOM_COLLECTION,
	SOURCE_ATOM_TUPLECONST,
	SOURCE_ATOM_NONE,
	SOURCE_ATOM_CLASS,
	SOURCE_ATOM_CALLFUNCTION,
	SOURCE_ATOM_COMPARE,
	SOURCE_ATOM_CONDJUMP,
	SOURCE_ATOM_JUMP,
	SOURCE_ATOM_DUP,
	SOURCE_ATOM_POP,
	SOURCE_ATOM_LOAD_ATTR,
	SOURCE_ATOM_UNPACK_SEQUENCE,
	SOURCE_ATOM_PRINT,
	SOURCE_ATOM_PRINTNEWLINE,
	SOURCE_ATOM_UNARYOPS,
	SOURCE_ATOM_BINARYOPS,
	SOURCE_ATOM_INPLACEOPS,
	SOURCE_ATOM_LOOP_START,
	SOURCE_ATOM_CONDITIONAL,
	SOURCE_ATOM_CONDITIONAL_LOOP,
	SOURCE_ATOM_RETURN,
	SOURCE_ATOM_GETITER,
	SOURCE_ATOM_FORITER,
	SOURCE_ATOM_SETUP_FINALLY,
	SOURCE_ATOM_SETUP_EXCEPT,
	SOURCE_ATOM_EXCEPT_PLACEHOLDER,
	SOURCE_ATOM_SETUP_WITH,
	SOURCE_ATOM_WITH_BLOCK,
	SOURCE_ATOM_WITH_BLOCK_GROUP,
	SOURCE_ATOM_IMPORT_FROM,
	SOURCE_ATOM_IMPORT_NAME,
	SOURCE_ATOM_DUMMY,
	SOURCE_ATOM_SLICE,
	SOURCE_ATOM_SLICE_W,
	SOURCE_ATOM_RAISE,
	SOURCE_ATOM_STORE_SUBSCR,
	SOURCE_ATOM_STORE_ATTR,
	SOURCE_ATOM_FLOAT,
	SOURCE_ATOM_BUILDSET,
	SOURCE_ATOM_BREAK_LOOP,
	SOURCE_ATOM_LIST_APPEND,
	SOURCE_ATOM_SIMPLE_CHAIN,
	SOURCE_ATOM_COMPLEX,
	SOURCE_ATOM_YIELD,
	SOURCE_ATOM_INT64,
	SOURCE_ATOM_DELEGATE,
	SOURCE_ATOM_STORE_SLICE,
	SOURCE_ATOM_DELETE_SLICE,
	SOURCE_ATOM_SET_ADD,
	SOURCE_ATOM_CONTINUE,
	SOURCE_ATOM_MAP_ADD,
	
	
};

enum STR_TYPES {
	SOURCE_STR_CONST,
	SOURCE_STR_NAME
};

void gen_build_call_function(py_function * fn, int idx, source_atom_tree * atoms, source_atom * out) {
	source_atom_callfunction * c = new source_atom_callfunction();
	
	
	out->type = SOURCE_ATOM_CALLFUNCTION; 
	py_instruction * inst = &fn->instruction_set[idx];
	
	out->data = c;
	int vidx = idx;
	source_atom * at;

	out->len = 1;
	c->varg_count = inst->arg & 0xF;
	c->kwarg_count = (inst->arg >> 8);
	
	c->vargs = new source_atom*[c->varg_count];
	c->kwargs = new source_atom*[2*c->kwarg_count];
	vidx = 0;
	if (inst->opcode == CALL_FUNCTION_VAR_KW) {
		c->kw = atoms->from_instruction(inst->stack_referrals[0]);
		c->va = atoms->from_instruction(inst->stack_referrals[1]);
		vidx = 2;
	}
	else if (inst->opcode == CALL_FUNCTION_VAR) {
		c->va = atoms->from_instruction(inst->stack_referrals[0]);
		vidx = 1;
	}
	else if (inst->opcode == CALL_FUNCTION_KW) {
		c->kw = atoms->from_instruction(inst->stack_referrals[0]);
		vidx = 1;
	}
	
	py_assert(inst->stack_referrals_sz == (c->varg_count + 2 * c->kwarg_count + 1) + vidx,
		"Function has invalid number of stack atoms %i != %i",c->varg_count + 2 * c->kwarg_count + 1,inst->stack_referrals_sz);
	
	int i;

	pylog("build call function %i %s",inst->off,inst->highlevel_name);
	for (i = 0; i < c->kwarg_count; i++) {
		at = atoms->from_instruction(inst->stack_referrals[vidx]);
		atoms->node_root_swap(at, out);
		vidx++;
		c->kwargs[i * 2+1] = at;
		out->len = out->len + at->len;
		at = atoms->from_instruction(inst->stack_referrals[vidx]);
		atoms->node_root_swap(at, out);
		vidx++;
		c->kwargs[i * 2 ] = at;
		py_assert(at->type == SOURCE_ATOM_STR, "Invalid key on kwargs");
		source_atom_str * st = (source_atom_str*)at->data;
		st->subtype = SOURCE_STR_NAME;
		out->len = out->len + at->len;
	}
	for (i = 0; i < c->varg_count; i++) {		
		at = atoms->from_instruction(inst->stack_referrals[vidx]);
		pylog("varg %i %i %llX",i, at->inst->off,at);
		atoms->node_root_swap(at, out);
		source_atom_tree_node * nn = earray_get(&at->referenced_nodes, 0, source_atom_tree_node*);
		
		vidx++;		
		c->vargs[i] = at;
		out->len = out->len + at->len;

		if (at->type == SOURCE_ATOM_BINARYOPS) {
			source_binary_op * b = (source_binary_op*)at->data;
			b->flags |= SOURCE_BINARY_NO_PARENTHESIS;
		}
	}
		
	// code object
	if (inst->stackbacks_sz > 0) {
		
		int poff = inst->stackbacks[0].stack_referrals[vidx]->off;
		pylog("inst st %s %i -- %i", inst->stackbacks[0].stack_referrals[0]->highlevel_name, inst->stackbacks[0].stack_referrals[0]->off, vidx);
		pylog("inst st %s %i -- %i", inst->stackbacks[0].stack_referrals[vidx]->highlevel_name, inst->stackbacks[0].stack_referrals[vidx]->off, vidx);
		int eq = 1;
		for (i = 1; i < inst->stackbacks_sz; i++) {
			if (inst->stackbacks[i].stack_referrals[vidx]->off != poff) {
				eq = 0;
				pylog("inst st %s %i -- %i", inst->stackbacks[i].stack_referrals[vidx]->highlevel_name, inst->stackbacks[i].stack_referrals[vidx]->off, i);
				break;
			}
		}
		py_assert(eq == 1, "Unknown call function multistack state %s %i",inst->highlevel_name,inst->off);
		at = atoms->from_off(poff);
	}
	else {
		at = atoms->from_instruction(inst->stack_referrals[vidx]);
	}
	
	if (c->varg_count > 0) {
		if (c->vargs[0]->type == SOURCE_ATOM_FUNCTION) {
			pylog("call result from MAKE_FUNCTION %i\n",at->type);
			source_atom_function * f = (source_atom_function*)c->vargs[0]->data;
			if (at->type == SOURCE_ATOM_STR) {
				source_atom_str * str = (source_atom_str*)at->data;	
				
				pylog("decorator %s\n",str->bytes);
				//TODO check if we are inside class code
				
				strcpy(f->annotation, str->bytes);
				c->flags |= SOURCE_FUNCTION_FLAG_SPECIAL_CLASS;				
			}
			else if (at->type == SOURCE_ATOM_CALLFUNCTION) {
				source_atom_callfunction * cf = (source_atom_callfunction*)at->data;
				if (cf->fn->type == SOURCE_ATOM_STR) {
					source_atom_str * str = (source_atom_str*)cf->fn->data;
					pylog("add decorator");
					strcpy(f->annotation, str->bytes);					
					//TODO get more args
					strcpy(f->annotation + strlen(str->bytes), "()");
					c->flags |= SOURCE_FUNCTION_FLAG_SPECIAL_CLASS;
				}
			}
		}
		else if (c->vargs[0]->type == SOURCE_ATOM_CALLFUNCTION) {
			source_atom_callfunction * c2 = (source_atom_callfunction*)c->vargs[0]->data;
			if (c2->flags & SOURCE_FUNCTION_FLAG_SPECIAL_CLASS) {
				pylog("nested decorator type %i", at->type);
				c->flags |= SOURCE_FUNCTION_FLAG_SPECIAL_CLASS;
				c2->flags |= SOURCE_FUNCTION_FLAG_NESTED_DECORATOR;
			}
		}
	}

	py_assert(at->len > 0, "Invalid code object atom for function");
	atoms->node_root_swap(at, out);
	
	c->fn = at;
	out->len += at->len;

	
}



void gen_build_function(py_function * fn, int idx, source_atom_tree * atoms, source_atom * out) {
	
	source_atom_function * funct = new source_atom_function();
	out->type = SOURCE_ATOM_FUNCTION;
	out->data = funct;
	py_instruction * inst = &fn->instruction_set[idx];
	py_assert(inst->stack_referrals_sz > 0, "Unknown MAKE_FUNCTION construct found");
	py_instruction * inst1 = inst->stack_referrals[0];

	un_code * c = (un_code*)inst1->arg_ptr;
	funct->code = c;
	py_assert(c->type.type == TYPE_CODE, "gen_source: Bad code on function?");
	
	funct->fnname = un_resolve_str(c->name);

	pylog("Build function for %s %llX", funct->fnname, funct);
	
	py_function * ffn = fn->nested_functions;
	
	while (ffn) {
		
		if (ffn->code == c) {			
			funct->func = ffn;
			break;
		}
		ffn = ffn->next;
	}

	if (!ffn) {
		ffn = fn->nested_closures;
		while (ffn) {
			
			if (ffn->code == c) {
				funct->func = ffn;
				break;
			}
			ffn = ffn->next;
		}
	}
	
	py_assert(ffn != NULL, "Invalid function on MAKE_FUNCTION");

	if (!strncmp(funct->fnname, "<lambda>",8)) {
		funct->flags |= SOURCE_FUNCTION_FLAG_LAMBDA;
	}
	if (!strncmp(funct->fnname, "<genexpr>", 9)) {		
		funct->flags |= SOURCE_FUNCTION_FLAG_GENERATOR;
	}
	if (!strncmp(funct->fnname, "<setcomp>", 9)) {
		funct->flags |= SOURCE_FUNCTION_FLAG_SETCOMP;
	}
	if (!strncmp(funct->fnname, "<dictcomp>", 10)) {
		funct->flags |= SOURCE_FUNCTION_FLAG_DICTCOMP;
	}

	
	
	source_atom * prev;
	prev = atoms->from_instruction(inst1);
	atoms->node_root_swap(prev, out);	
	out->len = 1;
	funct->defargs_sz = inst->arg;
	pylog("function flags %X, arg %i\n", funct->flags, inst->arg);

	int argst = 1;
	if (inst->opcode == MAKE_CLOSURE) {
		pylog("is a closure");
		source_atom * ax1 = atoms->from_instruction(inst->stack_referrals[1]);
		py_assert(ax1->type == SOURCE_ATOM_TUPLE || ax1->type == SOURCE_ATOM_TUPLECONST, "Unknown MAKE_CLOSURE form");
		argst = 2;
		atoms->node_root_swap(ax1, out);
	}

	if (!inst->arg) {
		return;
	}
	funct->defargs = new source_atom*[inst->arg];
	//py_assert(inst->stack_referrals_sz == 1 +funct->defargs_sz, "Invalid function on MAKE_FUNCTION");
	int i;
	for (i = argst; i < (int)inst->arg + argst; i++) {
		source_atom * at = atoms->from_instruction(inst->stack_referrals[i]);
		pylog("function %s defarg %i", ffn->name, at->type);
		funct->defargs[i - argst] = at;
		atoms->node_root_swap(at, out);
	}
	
	
	
}

void gen_build_class(py_function * fn, int idx, source_atom_tree * atoms, source_atom * out) {
	out->len = 1;
	out->type = SOURCE_ATOM_CLASS;
	py_instruction * inst = &fn->instruction_set[idx];
	py_instruction * inst_args[3];	
	
	py_assert(inst->stack_referrals_sz == 3, "Invalid class on atom construction");
	
	source_atom_class * cl = new source_atom_class();
	
	int j;
	
	for (j = 0; j < 3; j++) {		
		source_atom * at = atoms->from_instruction(inst->stack_referrals[j]);
		cl->params[j] = at;
		atoms->node_root_swap(at, out);
		py_assert(at->len > 0,"Invalid atom on class construction");
	}

	cl->baseclnames = atoms->from_instruction(inst->stack_referrals[1]);


	py_class * cls = fn->nested_classes;
	py_assert(cl->params[2]->type == SOURCE_ATOM_STR, "class not found on BUILD_CLASS");
	source_atom_str * st = (source_atom_str*)cl->params[2]->data;
	
	char * cname = st->bytes;

	source_atom_callfunction * cf = (source_atom_callfunction*)cl->params[0]->data;
	source_atom_function * gfn = (source_atom_function*)cf->fn->data;
	py_assert(cl->params[0]->type == SOURCE_ATOM_CALLFUNCTION, "Unknown class construct");
	
	while (cls) {
		if (cls->generator_function == gfn->code) {
		//if (!strcmp(un_resolve_str(cls->class_name), cname)) {
			cl->cls = cls;
			break;
		}
		cls = cls->next;
	}
	py_assert(cls != NULL, "class not found on BUILD_CLASS %s",cname);
	out->data = cl;

	py_assert(cl->params[0]->type == SOURCE_ATOM_CALLFUNCTION, "Unknown class construction");
	
	cl->basefn = cf->fn;	

	//py_function * m = cls->methods;
	//while (m) {
	//	gen_prepare_function(m);
//		m = m->next;
//	}
	
}


void gen_build_except_block(py_function * fn, int idx, source_atom_tree * atoms, source_atom * out) {

}


void gen_build_import_from(py_function * fn, int idx, source_atom_tree * atoms, source_atom * out) {
	py_instruction * inst = &fn->instruction_set[idx];
	out->data = un_resolve_str(inst->arg_ptr);
	out->type = SOURCE_ATOM_IMPORT_FROM;
	py_assert(inst->stack_referrals_sz == 1, "Invalid stack for IMPORT_FROM");
		
	out->len = 1;
}



void gen_build_store_var(py_function * fn, int idx, source_atom_tree * atoms, source_atom * out) {
	py_instruction * inst = &fn->instruction_set[idx];
	py_instruction * inst1;
	source_atom_store_val * sv = new source_atom_store_val();
	
	source_atom *tmp;
	int oidx = idx;
	
	py_assert(inst->stack_referrals_sz == 1, "STORE has no stack refs");
	
	if (inst->stack_referrals[0]->off == -1 && inst->stack_referrals[0]->opcode == EXCEPT_PLACEHOLDER) {
		tmp = atoms->get_except_placeholder();
	}
	else {
		tmp = atoms->from_instruction(inst->stack_referrals[0]);
	}
	out->type = SOURCE_ATOM_STORE_VAR;
	
	atoms->node_root_swap(tmp, out);
	py_assert(out->flags != 0x7FD, "Bad");
	sv->st_atom = tmp;
	
	py_assert(inst->arg_ptr != NULL, "Invalid atom on stack top for STORE");
	sv->var = un_resolve_str(inst->arg_ptr);

	out->len = tmp->len + 1;
	
	out->data = sv;	

	
}

void gen_str_fill_struct(int type, int subtype, source_atom_str * st, void * arg_ptr) {
	st->type = type;
	if (type == TYPE_STRING || type == TYPE_STRINGREF) {
		char * str = un_resolve_str(arg_ptr);
		st->size = un_str_size(arg_ptr);
		st->bytes = str;
		st->type = TYPE_STRING;
		st->subtype = subtype;
		return;
	}
	if (type == TYPE_UNICODE) {
		
		char tmp[8192];
		un_unicode * u = un_coerce_unicode(arg_ptr);
		unicode_to_ascii(tmp, u->original_bytes);

		char * lt = new char[strlen(tmp) + 1];
		strcpy(lt, tmp);
		st->bytes = lt;
		st->size = strlen(lt) + 1;
		st->type = TYPE_UNICODE;
		st->subtype = subtype;
		return;
	}
	py_assert(0, "source-gen: Unicode not implemented %i", type);
}

void gen_build_str(int type, int subtype, py_instruction * inst, source_atom* out) {
	source_atom_str * st = new source_atom_str();
	out->data = st;
	out->len = 1;
	out->type = SOURCE_ATOM_STR;
	out->start = inst->off;
	
	gen_str_fill_struct(type, subtype, st, inst->arg_ptr);
	
}

void gen_build_const_tuple(py_instruction * inst, source_atom* out) {
	un_tuple * tuple = (un_tuple*)inst->arg_ptr;
	out->len = 1;
	out->start = inst->off;
}

void gen_build_const(py_instruction * inst, source_atom* out) {
	un_type * typ = (un_type*)inst->arg_ptr;
	out->start = inst->off;

	switch (typ->type) {
	
	case TYPE_STRING:
	case TYPE_UNICODE:
	case TYPE_STRINGREF: {
		gen_build_str(typ->type, SOURCE_STR_CONST, inst, out);
		
		return;
	}
	
	case TYPE_LONG: {
		source_atom_int * it = new source_atom_int();
		it->val = un_resolve_int(inst->arg_ptr);
		out->data = it;
		out->len = 1;
		
		out->type = SOURCE_ATOM_INT;
		return;
	}
	case TYPE_TUPLE: {

		source_atom_tupleconst * ct = new source_atom_tupleconst();
		ct->tuple = (un_tuple*)inst->arg_ptr;
		out->data = ct;
		out->len = 1;
		out->type = SOURCE_ATOM_TUPLECONST;
		
		return;		
	}
	case TYPE_CODE: {
		// no atom
		out->len = 1;
		return;
	}
	case TYPE_NONE: {
		out->type = SOURCE_ATOM_NONE;
		out->start = inst->off;
		out->len = 1;
		
		return;
	}
	case TYPE_FLOAT: {
		out->type = SOURCE_ATOM_FLOAT;
		out->len = 1;
		un_double * d = un_coerce_double(typ);
		out->data = d;
		return;
	}
	case TYPE_BINARY_COMPLEX: {
		un_complex * c = un_coerce_complex(typ);
		out->type = SOURCE_ATOM_COMPLEX;
		out->len = 1;
		
		out->data = c;
		
		return;
	}
	case TYPE_INT64: {
		source_atom_int64 * it = new source_atom_int64();
		it->val = un_resolve_int(inst->arg_ptr);
		out->data = it;
		out->len = 1;

		out->type = SOURCE_ATOM_INT64;
		
		return;
	}
	}

	py_assert(0, "source-gen: Const not implemented %c %i", typ->type,typ->type);
}

void ** gen_get_stack_elems(int n, py_function * fn, int idx, source_atom_tree * atoms, int * len,
	int ref, source_atom * parent) {
	
	py_instruction * inst = &fn->instruction_set[idx];
	void ** l = new void*[n];
	int k = n - 1;

	(*len) = 0;
	
	py_assert(n == inst->stack_referrals_sz, "Invalid size on instruction stack %i != %i (%llX)", n, inst->stack_referrals_sz,inst);
	int i;
	for (i = 0; i < n; i++) {
		py_instruction * pinst = inst->stack_referrals[i];
		source_atom * at = atoms->from_instruction(inst->stack_referrals[i]);		
		
		py_assert(at->type != 0, "Stack requested on non solved atom %i %s",
			inst->stack_referrals[i]->off, inst->stack_referrals[i]->highlevel_name);
		l[k--] = at;
		atoms->node_root_swap(at, parent);
		(*len) = (*len) + at->len;
		
	}
	

	return l;
}

int gen_get_inst_start_ref(py_function * fn, int idx, source_atom_tree * atoms) {
	py_instruction * inst = &fn->instruction_set[idx];
	if (inst->stack_referrals_sz == 0) {
		return inst->off;
	}
	
	source_atom * st = atoms->from_instruction(inst->stack_referrals[inst->stack_referrals_sz - 1]);

	py_assert(st->len > 0, "Invalid atom on instruction ref, inst was %s, calling inst was %s",
		inst->stack_referrals[inst->stack_referrals_sz - 1]->highlevel_name,inst->highlevel_name);
	return st->start;
}

void gen_build_list(int type, py_function * fn, int idx, source_atom_tree * atoms, source_atom * out) {
	
	int list_size = fn->instruction_set[idx].arg;

	out->type = type;
	source_atom_list * l = new source_atom_list();
	out->data = l;
	l->size = list_size;
	if (list_size == 0) {
		out->len = 1;
		l->elems = NULL;
		return;
	}
	
	int k = list_size-1;
	
	
	int full_len = 0;
	
	l->elems = (source_atom**)gen_get_stack_elems(list_size, fn, idx, atoms, &full_len,idx,out);
	
	//out->start = gen_get_inst_start_ref(fn, idx, atoms);
	out->len = full_len+1;
}

void flag_flow_inst(py_instruction * inst, source_atom_tree * atoms, source_atom * atom, 
		flow_graph * nodes ) {

	int i;
	for(i=0;i<nodes->nodes.size;i++) {
		flow_node * node = earray_get(&nodes->nodes,i,flow_node*);
		if (inst == node->final_inst) {
			pylog("node inst found %i\n",node->initial_inst->off);
			source_atom * at = atoms->from_instruction(node->initial_inst);
			py_assert(at->idx >= 0,"Bad atom on flow flag");
			
			int j;
			for(j=0;j<at->referenced_nodes.size;j++) {
				source_atom_tree_node * pnode = earray_get(&at->referenced_nodes,j,source_atom_tree_node*);
				source_atom_tree_node * p = pnode->parent;
				
				while (p) {
					pylog("parent %llX\n", p->atom);
					if (p->atom == atom) {
						node->flags |= FLOW_FLAG_PURE_CONDITIONAL;
						pylog("node is pure conditional\n");
						
						break;
					}
					p = p->parent;
				}
			}
			
		}
	}
	
}


void gen_source_obj(py_function * fn, int idx, source_atom_tree * atoms, source_atom * out) {
	py_instruction * inst = &fn->instruction_set[idx];
	out->flags = 0;
	out->inst = inst;
	py_instruction * inst1 = &fn->instruction_set[idx - 1];
	int flen;
	out->idx = idx;

	char tmp[8192];
	disasm_pretty_print(tmp, inst, -1);
	pylog("-- fun %s -- %s\n", fn->name,tmp);
	if (inst->stackbacks_sz > 0) {
		pylog("multiple stackbacks");
		
		//py_assert(inst->stack_referrals_sz == 1, "Unknown inst stackback");	

	}
	
	switch (inst->opcode) {
	case BUILD_LIST: {
		gen_build_list(SOURCE_ATOM_LIST, fn, idx, atoms, out);
		break;
	}
	case CONTINUE_LOOP: {
		out->type = SOURCE_ATOM_CONTINUE;
		out->len = 1;
		break;
	}
	case YIELD_VALUE: {
		out->type = SOURCE_ATOM_YIELD;
		source_atom * at = atoms->from_instruction(inst->stack_referrals[0]);
		out->data = at;
		atoms->node_root_swap(at, out);
		out->len = 1;
		break;
	}
	case LOAD_CONST: {		
		gen_build_const(inst, out);		
		break;
	}
	case SET_ADD: {
		out->type = SOURCE_ATOM_SET_ADD;
		out->len = 1;
		out->data = inst->stack_referrals[0];
		break;
	}
	case LIST_APPEND: {
		out->type = SOURCE_ATOM_LIST_APPEND;
		out->len = 1;
		out->data = inst->stack_referrals[0];
		break;
	}
	case LOAD_CLOSURE:
	case LOAD_DEREF:
	case LOAD_FAST: 
	case LOAD_GLOBAL: {
		int type = ((un_type*)inst->arg_ptr)->type;
		py_assert(type == TYPE_STRING || type == TYPE_STRINGREF ||
			type == TYPE_UNICODE,"Invalid type for LOAD_GLOBAL/FAST/DEREF");

		gen_build_str(type, SOURCE_STR_NAME, inst, out);
		
		break;
	}
	case BREAK_LOOP: {
		out->len = 1;
		out->type = SOURCE_ATOM_BREAK_LOOP;
		break;
	}
	case END_FINALLY:
	case POP_BLOCK:
	case WITH_CLEANUP:
	case ROT_TWO:
	case ROT_THREE:
	case OPCODE_DUMMY:
	case LOAD_LOCALS: {
		out->len = 1;
		out->type = SOURCE_ATOM_DUMMY;
		break;
	}
	case LOAD_ATTR: {
		source_atom_loadattr * attr = new source_atom_loadattr;
		out->type = SOURCE_ATOM_LOAD_ATTR;
		source_atom * at = atoms->from_instruction(inst->stack_referrals[0]);
		attr->ref_atom = at;
		py_assert(at->len > 0, "Invalid atom on stack top %s",at->inst->highlevel_name);
		un_type * typ = (un_type*)inst->arg_ptr;
		

		gen_str_fill_struct(typ->type, SOURCE_STR_NAME, &attr->attr, inst->arg_ptr);


		atoms->node_root_swap(at, out);
		out->data = attr;
		out->len = 1;

		break;
	}

	case IMPORT_NAME: {
		source_import_name * n = new source_import_name();
		out->data = n;
		out->type = SOURCE_ATOM_IMPORT_NAME;
		py_assert(inst->stack_referrals_sz == 2, "Unknown IMPORT_NAME found");

		n->fromlist = atoms->from_instruction(inst->stack_referrals[0]);
		n->length = atoms->from_instruction(inst->stack_referrals[1]);

		py_assert(n->fromlist->type == SOURCE_ATOM_TUPLECONST || n->fromlist->type == SOURCE_ATOM_NONE,
			"Unknown IMPORT in fromlist (%i)",n->fromlist->type);
		if (n->fromlist->type == SOURCE_ATOM_TUPLECONST) {
			source_atom_tupleconst * tdata = (source_atom_tupleconst*)n->fromlist->data;
			tdata->flags |= ATOM_TUPLE_FLAG_NO_PARENTHESIS;
		}
		
		atoms->node_root_swap(n->fromlist, out);
		atoms->node_root_swap(n->length, out);


		strcpy(n->symbol, un_resolve_str(inst->arg_ptr));
		out->len = 1;
		
		break;
	}
	case LOAD_NAME: {
		un_type * typ = (un_type*)inst->arg_ptr;
		gen_build_str(typ->type, SOURCE_STR_NAME, inst, out);


		break;
	}
	case SLICE:
	case SLICE_2:		
	case SLICE_3:		
	case SLICE_1: {
		out->type = SOURCE_ATOM_SLICE_W;
		source_atoms_slice * slice = new source_atoms_slice();

		
		int	size = 2;
		
		slice->size = size;

		py_assert(inst->stack_referrals_sz > 0, "Invalid stack top for SLICE (%i)", inst->stack_referrals_sz);

		if (inst->opcode == SLICE_2) {
			slice->params[0] = NULL;
			slice->params[1] = atoms->from_instruction(inst->stack_referrals[0]);
			atoms->node_root_swap(slice->params[1], out);
			slice->origin = atoms->from_instruction(inst->stack_referrals[1]);
		}
		else if (inst->opcode == SLICE_1) {			
			slice->params[0] = atoms->from_instruction(inst->stack_referrals[0]);			
			slice->params[1] = NULL;
			atoms->node_root_swap(slice->params[0], out);
			slice->origin = atoms->from_instruction(inst->stack_referrals[1]);
		}
		else if (inst->opcode == SLICE_3) {
			slice->params[0] = atoms->from_instruction(inst->stack_referrals[0]);
			slice->params[1] = atoms->from_instruction(inst->stack_referrals[1]);
			atoms->node_root_swap(slice->params[0], out);
			atoms->node_root_swap(slice->params[1], out);
			slice->origin = atoms->from_instruction(inst->stack_referrals[2]);
		}
		else if (inst->opcode == SLICE) {
			slice->params[0] = NULL;
			slice->params[1] = NULL;
			slice->origin = atoms->from_instruction(inst->stack_referrals[0]);
		}

		atoms->node_root_swap(slice->origin, out);
		
		out->data = slice;
		out->len = 1;
		break;
	}
	case BUILD_SLICE: {
		out->type = SOURCE_ATOM_SLICE;
		source_atoms_slice * slice = new source_atoms_slice();
		
		int	size = inst->arg;
		
		
		slice->size = size;
		int i;
		py_assert(inst->stack_referrals_sz == slice->size,"Invalid stack top for SLICE (%i)",inst->stack_referrals_sz);
		for (i = 0; i < slice->size; i++) {
			slice->params[i] = atoms->from_instruction(inst->stack_referrals[i]);
			atoms->node_root_swap(slice->params[i], out);
		}
		out->data = slice;
		out->len = 1;
		break;
	}
	
	case BUILD_TUPLE: {
		gen_build_list(SOURCE_ATOM_TUPLE, fn, idx, atoms, out);
		break;
	}

	case STORE_SUBSCR: {
		py_assert(inst->stack_referrals_sz == 3, "Invalid stack size for STORE_SUBSCR (%i)",inst->stack_referrals_sz);
		source_atom * at = atoms->from_instruction(inst->stack_referrals[0]);
		atoms->node_root_swap(at, out);

		source_atom_store_subscr_val * subs = new source_atom_store_subscr_val();
		subs->subscr = at;
		subs->st_atom = atoms->from_instruction(inst->stack_referrals[2]);
		atoms->node_root_swap(subs->st_atom, out);

		at = atoms->from_instruction(inst->stack_referrals[1]);
		atoms->node_root_swap(at, out);

		subs->var = at;
		out->data = subs;
		out->len = 1;
		out->type = SOURCE_ATOM_STORE_SUBSCR;
		
		break;
	}
	case STORE_ATTR: {
		out->type = SOURCE_ATOM_STORE_ATTR;
		source_atom_store_attr * st = (source_atom_store_attr*)new source_atom_store_attr();
		st->obj = atoms->from_instruction(inst->stack_referrals[0]);
		st->st_atom = atoms->from_instruction(inst->stack_referrals[1]);
		atoms->node_root_swap(st->obj, out);
		atoms->node_root_swap(st->st_atom, out);

		st->var = un_resolve_str(inst->arg_ptr);
		out->data = st;
		out->len = 1;
		break;
	}
	case STORE_DEREF:
	case STORE_FAST:
	case STORE_NAME: {			
		gen_build_store_var(fn, idx, atoms, out);			
		break;
	}
	case DELETE_SUBSCR:
	case DELETE_SLICE:
	case DELETE_SLICE_1:
	case DELETE_SLICE_2:
	case DELETE_SLICE_3: {
		out->type = SOURCE_ATOM_DELETE_SLICE;
		source_atoms_delete_slice * sd = new source_atoms_delete_slice();
		out->data = sd;		
		out->len = 1;
		sd->type = inst->opcode;
		int disp = 0;
		if (inst->opcode == DELETE_SLICE) {
			sd->st = atoms->from_instruction(inst->stack_referrals[0]);
			disp = 0;
		}
		else if (inst->opcode == DELETE_SLICE_1 || inst->opcode == DELETE_SLICE_2 || inst->opcode == DELETE_SUBSCR) {
			py_assert(inst->stack_referrals_sz == 2, "Unknown DELETE_SLICE construct");
			sd->st = atoms->from_instruction(inst->stack_referrals[1]);
			sd->params[0] = atoms->from_instruction(inst->stack_referrals[0]);		
			
			disp = 1;
		}
		else if (inst->opcode == DELETE_SLICE_3) {
			sd->st = atoms->from_instruction(inst->stack_referrals[2]);
			sd->params[0] = atoms->from_instruction(inst->stack_referrals[0]);
			sd->params[1] = atoms->from_instruction(inst->stack_referrals[1]);			
			disp = 2;
		}
		int i;
		for (i = 0; i < disp; i++) {
			atoms->node_root_swap(sd->params[i], out);
		}
		atoms->node_root_swap(sd->st, out);
		break;
	}
	case STORE_SLICE:
	case STORE_SLICE_1:
	case STORE_SLICE_2:
	case STORE_SLICE_3: {		
		
		source_atoms_store_slice * st = new source_atoms_store_slice();
		st->type = inst->opcode;
		int i;
		int disp = 0;
		if (inst->opcode == STORE_SLICE) {
			st->st = atoms->from_instruction(inst->stack_referrals[0]);
			st->dest = atoms->from_instruction(inst->stack_referrals[1]);
			disp = 0;
		}
		else if (inst->opcode == STORE_SLICE_1 || inst->opcode == STORE_SLICE_2) {
			st->st = atoms->from_instruction(inst->stack_referrals[1]);
			st->params[0] = atoms->from_instruction(inst->stack_referrals[0]);
			st->dest = atoms->from_instruction(inst->stack_referrals[2]);
			disp = 1;
		}
		else if (inst->opcode == STORE_SLICE_3) {
			st->st = atoms->from_instruction(inst->stack_referrals[2]);
			st->params[0] = atoms->from_instruction(inst->stack_referrals[0]);
			st->params[1] = atoms->from_instruction(inst->stack_referrals[1]);
			st->dest = atoms->from_instruction(inst->stack_referrals[3]);
			disp = 2;
		}		
		for (i = 0; i < disp; i++) {
			atoms->node_root_swap(st->params[i], out);
		}
		atoms->node_root_swap(st->st, out);
		atoms->node_root_swap(st->dest, out);
		out->data = st;		
		out->type = SOURCE_ATOM_STORE_SLICE;
		out->len = 1;

		
		break;
	}
	case IMPORT_FROM: {
		gen_build_import_from(fn, idx, atoms, out);
		break;
	}
	case SETUP_WITH: {
		out->data = atoms->from_instruction(inst->stack_referrals[0]);
		out->type = SOURCE_ATOM_SETUP_WITH;
		out->len = 1;
		atoms->node_root_swap((source_atom*)out->data, out);
		
		break;
	}
	case BUILD_CLASS: {
		gen_build_class(fn, idx, atoms, out);
		break;
	}
	case SETUP_FINALLY: {
		out->type = SOURCE_ATOM_SETUP_FINALLY;
		out->len = 1;
		break;
	}
	case SETUP_EXCEPT: {
		int j;
		source_atom * at = atoms->from_off(inst->to_jmp);
		at->except_base = 1;
		pylog("except base set on %i\n", inst->to_jmp);
		out->len = 1;
		out->type = SOURCE_ATOM_SETUP_EXCEPT;
		break;
	}
	case FOR_ITER: {
		
		source_atom * at = atoms->from_instruction(inst->stack_referrals[0]);
		out->type = SOURCE_ATOM_FORITER;
		out->data = at;
		out->len = 1;
		atoms->node_root_swap(at, out);
		break;
	}
	case GET_ITER: {
		source_atom * at = atoms->from_instruction(inst->stack_referrals[0]);
		out->data = at;
		out->type = SOURCE_ATOM_GETITER;
		out->len = 1;
		atoms->node_root_swap(at, out);
		break;
	}
	case MAP_ADD: {
		out->type = SOURCE_ATOM_MAP_ADD;
		out->len = 1;
		source_atom_keyval * kv = new source_atom_keyval();
		py_assert(inst->stack_referrals_sz == 2, "Invalid MAP_ADD found");
		kv->key = atoms->from_instruction(inst->stack_referrals[0]);
		kv->value = atoms->from_instruction(inst->stack_referrals[1]);
		atoms->node_root_swap(kv->key, out);
		out->data = kv;
		//atoms->node_root_swap(kv->value, out);
		break;
	}
	case STORE_MAP: {
		py_assert(inst->stack_referrals_sz == 3, "Unknown map construct");
		source_atom * map = atoms->from_instruction(inst->stack_referrals[2]);

		while (map->inst->opcode == STORE_MAP) {
			map = atoms->from_instruction(map->inst->stack_referrals[2]);
		}
		py_assert(map->type == SOURCE_ATOM_BUILDSET,"Unknown map construct");
		
		source_atom_buildset * bs = (source_atom_buildset*)map->data;
		source_atom * key = atoms->from_instruction(inst->stack_referrals[0]);
		source_atom * value = atoms->from_instruction(inst->stack_referrals[1]);
	
		bs->add_key_pair(key,value);
		atoms->node_root_swap(key, map);
		atoms->node_root_swap(value, map);
		atoms->node_root_swap(out, map);

		map->flags |= ATOM_FLAG_DELEGATE;

		out->type = SOURCE_ATOM_DELEGATE;
		out->data = map;
		
		break;
	}
	case BUILD_SET:
	case BUILD_MAP: {
		source_atom_buildset * bs = new source_atom_buildset();
		out->data = bs;
		out->len = 1;
		out->type = SOURCE_ATOM_BUILDSET;
		break;
	}
	case UNPACK_SEQUENCE: {
		out->len = 1;
		out->type = SOURCE_ATOM_UNPACK_SEQUENCE;
		source_atom_unpacked_sequence * us = new source_atom_unpacked_sequence();
		out->data = us;
		us->used = 0;
		us->size = inst->arg;
		py_assert(1 == inst->stack_referrals_sz, "UNPACK_SEQUENCE has invalid number of stack referrals");
		source_atom * at = atoms->from_instruction(inst->stack_referrals[0]);
		if (at->type == SOURCE_ATOM_STR) {
			source_atom_str * str = (source_atom_str*)at->data;

			if (str->bytes[0] == '.' && str->bytes[1] >= '0' && str->bytes[1] <= '9') {
				// special unpack
				int nsize = us->size;
				pylog("UNPACK_SEQUENCE size %i", nsize);
				//gen_solve_unpack_seq(at, nsize,fn);
			}
		}
		atoms->node_root_swap(at, out);
		us->rt = at;
		out->len += at->len;
		
		break;
	}
	case POP_TOP: {
		out->len = 1;
		out->type = SOURCE_ATOM_POP;
		
		if (!out->except_base) {

			py_assert(inst->stack_referrals_sz == 1, "Unknown pop construct");
			
			if (inst->stack_referrals[0]->opcode == EXCEPT_PLACEHOLDER) {
				out->data = atoms->get_except_placeholder();
				break;
			}
			
			source_atom * at = atoms->from_instruction(inst->stack_referrals[0]);
			py_assert(at->len > 0, "Invalid atom on stack top %s", inst->stack_referrals[0]->highlevel_name);
			out->data = at;
			atoms->node_root_swap(at, out);
		}
		else {
			out->data = atoms->get_except_placeholder();
		}
		
		break;
	}
	case DUP_TOP: {
		out->len = 1;
		out->type = SOURCE_ATOM_DUP;
		out->data = NULL;
		
		if (!out->except_base) {
			source_atom * at = atoms->from_instruction(inst->stack_referrals[0]);
			py_assert(at->len > 0, "Invalid atom on stack top");
			out->data = at;
			atoms->node_root_swap(at, out);
		}
		else {
			if (inst->stack_referrals[0]->opcode == EXCEPT_PLACEHOLDER) {
				pylog("dup placeholder\n");
				source_atom * at = atoms->get_except_placeholder();
				out->data = at;
			}
			else {
				py_assert(0, "Unknown type on DUP");
			}
		}

		break;
	}
	case CALL_FUNCTION_VAR:
	case CALL_FUNCTION_VAR_KW:
	case CALL_FUNCTION_KW:
	case CALL_FUNCTION: {
		gen_build_call_function(fn,idx, atoms, out);
		
		break;
	}
	case RETURN_VALUE: {
		
		py_assert(inst->stack_referrals_sz < 2, "Invalid return construct %s %i",inst->highlevel_name,inst->stack_referrals_sz);
		if (inst->stack_referrals_sz == 0) {
			// this might happen if return cannot be reached
			out->type = SOURCE_ATOM_DUMMY;
			break;
		}
		
		out->data = atoms->from_instruction(inst->stack_referrals[0]);
		out->type = SOURCE_ATOM_RETURN;
		out->len = 1;
		atoms->node_root_swap((source_atom*)out->data, out);
		break;
	}
	case COMPARE_OP: {
		source_atom_compare * cmp = new source_atom_compare;
		void ** data = gen_get_stack_elems(2, fn, idx, atoms, &flen,idx,out);

		cmp->params = (source_atom **)data;
		py_assert(cmp->params[0]->type != 0, "Invalid atom on compare");
		py_assert(cmp->params[1]->type != 0, "Invalid atom on compare");
		cmp->len = 2;
		cmp->op = inst->arg;
		out->type = SOURCE_ATOM_COMPARE;
		out->data = cmp;
		out->len = 1;
		source_atom * at = atoms->from_instruction(inst->stack_referrals[0]);
		
		out->start = at->start;
		
		break;
	}
	case PRINT_NEWLINE: {
		source_atom_tree_node * n = out->get_tree_top_ref();
		
		if (n->prev && n->prev->atom->type == SOURCE_ATOM_PRINT) {
			out->data = n->prev->atom;
		}
		else {
			out->data = NULL;
		}
		
		out->type = SOURCE_ATOM_PRINTNEWLINE;
		out->len = 1;
		break;
	}
	case PRINT_ITEM: {
		py_assert(inst->stack_referrals_sz == 1,"Invalid print atom");
		out->data = atoms->from_instruction(inst->stack_referrals[0]);
		out->type = SOURCE_ATOM_PRINT;
		out->len = 1;
		atoms->node_root_swap((source_atom*)out->data, out);
		break;
	}
	case UNARY_POSITIVE:
	case UNARY_NEGATIVE:
	case UNARY_NOT: {
		source_atoms_ops * ops = new source_atoms_ops;
		
		out->type = SOURCE_ATOM_UNARYOPS;
		out->len = 1;
		
		py_assert(inst->stack_referrals_sz == 1, "Invalid number of arguments on unary inst (%i)",inst->stack_referrals_sz);
		
		source_atom * at = atoms->from_instruction(inst->stack_referrals[0]);
		ops->param1 = at;
		ops->param2 = NULL;
		ops->op = inst->opcode;
		py_assert(at->len > 0, "Invalid atom on stack top");
		out->data = ops;
		pylog("swap %i", at->inst->off);
		atoms->node_root_swap(at, out);

		if (inst->stackbacks_sz > 0) {
			int i;
			for (i = 0; i < inst->stackbacks_sz; i++) {
				at = atoms->from_instruction(inst->stackbacks[i].stack_referrals[0]);
				atoms->node_root_swap(at, out);
			}
		}

		break;
	}
	case SETUP_LOOP: {
		out->type = SOURCE_ATOM_LOOP_START;
		out->flags |= ATOM_FLAG_LOOP_START;
		out->len = 1;
		break;
	}
	case RAISE_VARARGS: {
		out->type = SOURCE_ATOM_RAISE;
		source_atom_raise * r = new source_atom_raise();
		r->size = inst->arg;
		int i;
		py_assert(inst->stack_referrals_sz == r->size, "Invalid RAISE_VARARGS");
		for (i = 0; i < r->size; i++) {
			r->params[i] = atoms->from_instruction(inst->stack_referrals[i]);
			atoms->node_root_swap(r->params[i], out);
		}
		out->len = 1;
		out->data = r;
		break;
	}
	case JUMP_ABSOLUTE:
	case JUMP_FORWARD: {
		out->type = SOURCE_ATOM_JUMP;
		out->len = 1;
		out->data = 0;
		break;
	}
	case JUMP_IF_FALSE_OR_POP:
	case POP_JUMP_IF_TRUE:
	case POP_JUMP_IF_FALSE: {
		
		//py_assert(inst1->opcode == COMPARE_OP, "Unknown conditional jump %s", inst1->highlevel_name);
		out->type = SOURCE_ATOM_CONDJUMP;
		source_atom * atom1 = atoms->from_instruction(inst);	
		source_atom * aref = atoms->from_instruction(inst->stack_referrals[0]);

		source_atom_tree_node * atp = atoms->node_root_swap(aref, out);
		out->data = aref;

		atom1--;		
		while (!atom1->len) {			
			atom1--;
		}
		if (atom1->flags & ATOM_FLAG_LOOP_START) {
			out->flags |= ATOM_FLAG_LOOP_START;
		}
		out->len = atom1->len + 1;
				
		flag_flow_inst(inst,atoms,out,fn->flow_nodes);
		
		break;
	}
	case INPLACE_ADD:
	case INPLACE_SUBTRACT: {
		source_inplace_op * iop = new source_inplace_op();
		py_assert(inst->stack_referrals_sz == 2, "Invalid inplace op");
		iop->op1 = atoms->from_instruction(inst->stack_referrals[1]);
		iop->op2 = atoms->from_instruction(inst->stack_referrals[0]);

		atoms->node_root_swap(iop->op1, out);
		atoms->node_root_swap(iop->op2, out);

		iop->type = inst->opcode;
		out->data = iop;
		out->type = SOURCE_ATOM_INPLACEOPS;
		out->len = 1;
		break;
	}
	case BINARY_POWER:
	case BINARY_LSHIFT:
	case BINARY_FLOOR_DIVIDE:
	case BINARY_AND:
	case BINARY_RSHIFT:
	case BINARY_MODULO:
	case BINARY_MULTIPLY:
	case BINARY_DIVIDE:
	case BINARY_SUBTRACT:
	case BINARY_SUBSCR:
	case BINARY_ADD: {
		
		if (inst->stackbacks_sz > 1) {
			out->flags |= ATOM_FLAG_MULTISTACK;
		}
		out->type = SOURCE_ATOM_BINARYOPS;
		out->len = 1;
		source_binary_op * sb = new source_binary_op();
		
		py_assert(inst->stack_referrals_sz == 2, "Unknown binary op %s format (%i)", inst->highlevel_name,inst->stack_referrals_sz);
		sb->op1 = atoms->from_instruction(inst->stack_referrals[0]);
		sb->op2 = atoms->from_instruction(inst->stack_referrals[1]);
		
		atoms->node_root_swap(sb->op1, out);
		atoms->node_root_swap(sb->op2, out);
		sb->type = inst->opcode;
		out->data = sb;
		
		break;		
	}
	case MAKE_CLOSURE:
	case MAKE_FUNCTION: {		
		gen_build_function(fn, idx, atoms, out);
		// resolve the next function here
		source_atom_function * gf = (source_atom_function*)out->data;
		
		gen_prepare_function(gf->func);
		
		
		break;
	}
	default: {
		//py_assert(0, "Unimplemented inst %s",inst->highlevel_name);
	}
	}
	//out->start = gen_get_inst_start_ref(fn, idx, atoms);
	out->tos_op_in = 0;
	out->tos_op_out = 0;

	int i;
	for (i = idx- (out->len-1); i <= idx; i++) {
		py_instruction * inst = &fn->instruction_set[i];
		
		if (inst->tos_op_out > out->tos_op_in) {
			int dout = inst->tos_op_out - out->tos_op_in;
			out->tos_op_out += dout;
			out->tos_op_in = 0;
		}
		else {
			out->tos_op_in -= inst->tos_op_out;
		}

		out->tos_op_in += inst->tos_op_in;				
		
	}
	
}

void gen_source_function(py_function * fn) {
	pylog("gen starting on function: %s -- %llX", fn->name,fn);
	
	int i;
	int max_off = fn->instruction_set[fn->instruction_set_size - 1].off + 1;
	pylog("atoms size %i", max_off);
	py_assert(fn->atoms == NULL, "gen called on already generated function");

	source_atom_tree * atoms = new source_atom_tree(max_off);
	fn->atoms = atoms;
	atoms->except_placeholder.type = SOURCE_ATOM_EXCEPT_PLACEHOLDER;
		
	for (i = 0; i < fn->instruction_set_size; i++) {
		py_instruction * inst = &fn->instruction_set[i];
		source_atom * at = atoms->from_instruction(inst);
		atoms->add_root_node(at);
		
		gen_source_obj(fn, i, atoms, at);
		

	}
	
	fn->atoms_sz = max_off;
}

void flow_set_break(flow_node * n, source_atom_tree * atoms) {
	source_atom *at;
	at = atoms->from_instruction(n->initial_inst);
	py_assert(at->referenced_nodes.size == 1, "Unknown structure on if block exit");
	source_atom_tree_node * p = earray_get(&at->referenced_nodes, 0, source_atom_tree_node*);

	while (p->parent) {
		p = p->parent;
	}
	at = p->atom;
	at->flags |= ATOM_FLAG_BREAK_LINE;
}

enum chain_type {
	CHAIN_TYPE_COND,
	CHAIN_TYPE_BLOCK,
	CHAIN_DIRECTION_AND,
	CHAIN_DIRECTION_OR,
};

#define CHAIN_FLAG_ENDCHAIN 			0x1
#define CHAIN_FLAG_STARTCHAIN 			0x2
#define CHAIN_FLAG_ENDCOND 				0x4
#define CHAIN_FLAG_PATH 				0x8
#define CHAIN_FLAG_NO_PATH 				0x10
#define CHAIN_FLAG_NO_PATH_NO_DESC		0x20
#define CHAIN_FLAG_SIMPLE				0x40
#define CHAIN_FLAG_INLINE				0x80
#define CHAIN_FLAG_CONTINUE				0x100
#define CHAIN_FLAG_NODECORATION			0x200
#define CHAIN_FLAG_NOT					0x400


typedef struct cond_chain {
	flow_node * node;
	source_atom * atom_top;
	struct cond_chain * right;
	struct cond_chain * left;
	struct cond_chain * chain_top;
	int type;
	int direction;
	int endcount;
	int flags;
	source_atom_inline_for_construct * lambda;
	source_atom * extra_data;
	source_atom *inline_atoms[2];
	cond_chain() {
		memset(this, 0, sizeof(cond_chain));
	}
} cond_chain;

void flow_set_indent(py_function * fn, flow_node * n, int depth, source_atom_tree * atoms, flow_node * desc, int flags) {
	py_instruction * inst = n->initial_inst;
	pylog("setting indent %i, depth: %i %i\n", n->begin_off, depth, n->desired_depth);
	source_atom *at;
	
	if (n->desired_depth >= 0 && n->desired_depth < depth) {
		pylog("not setting\n");
		return;
	}
	
	n->depth = depth;
	n->desired_depth = depth;
	
	at = atoms->from_instruction(inst);
	

	for (;;) {
		at->depth = depth;
		if (inst == n->final_inst) {
			break;
		}
		inst++;
		at = atoms->from_instruction(inst);
	}
	
	if (n->outgoing.size == 1 ) {
		flow_edge * e = earray_get(&n->outgoing, 0, flow_edge*);
		flow_node * next = e->node;
		if (desc) {			
			if (next != desc && !(e->flags & FLOW_EDGE_FLAG_LOOP)) {
				pylog("set desc %i to %i\n", next->begin_off,depth);
				if (0 && flags & CHAIN_FLAG_NO_PATH_NO_DESC && next->desired_depth == -1) {
					flow_set_indent(fn, next, depth-1, atoms, desc, 0);
				}
				else {
					flow_set_indent(fn, next, depth, atoms, desc, flags);
				}
			}
		}
		else {
			pylog("set nodesc %i to %i\n", next->begin_off, depth);
			if (0&&flags & CHAIN_FLAG_NO_PATH_NO_DESC && next->desired_depth == -1) {				
				flow_set_indent(fn, next, depth-1, atoms, desc, 0);
			}
			else {
				flow_set_indent(fn, next, depth, atoms, desc, flags);
			}
		}
	}

}

void set_visited(flow_node * n, int * visited) {
	py_instruction * inst;
	
	for (inst = n->initial_inst;; inst++) {
		visited[inst->idx] = 1;
		
		if (inst == n->final_inst) {
			return;
		}
	}
}

struct s_queue_entry;
struct s_queue_entry * queue_pool_get();
void queue_pool_release(struct s_queue_entry * e);
// add mutex

typedef struct s_queue_entry {
	s_queue_entry * next;
	s_queue_entry * prev;
	void * data;
	s_queue_entry() {
		next = prev = NULL;
	}
} s_queue_entry;

typedef struct s_queue {
	s_queue_entry * head;
	s_queue_entry * tail;
	s_queue() {
		tail = head = NULL;
	}

	void add(void * data) {
		s_queue_entry * entry = queue_pool_get();
		entry->data = data;
		if (tail) {
			tail->next = entry;
			entry->prev = tail;			
		}
		else {
			head = entry;
		}
		tail = entry;
	}

	void * remove_first() {
		if (head) {
			s_queue_entry * entry = head;
			head = head->next;
			head->prev = NULL;
			void * data = entry->data;
			queue_pool_release(entry);
			return data;
		}
		return NULL;
	}
} s_queue;

s_queue_entry * queue_pool = NULL;


s_queue_entry * queue_pool_get() {
	if (!queue_pool) {
		int i;
		for (i = 0; i < 32; i++) {
			s_queue_entry * entry = new s_queue_entry();
			entry->next = queue_pool;
			entry->prev = NULL;
			if (entry->next) {
				entry->next->prev = entry;
			}
			queue_pool = entry;
		}
	}

	s_queue_entry * t = queue_pool;
	queue_pool = queue_pool->next;
	t->next = t->prev = NULL;
	
	return t;
}

void queue_pool_release(s_queue_entry * e) {
	e->next = queue_pool;
	if (e->next) {
		e->next->prev = e;
	}
}

void flip_chain(cond_chain * cc) {
	if (cc->direction == CHAIN_DIRECTION_AND) {
		cc->direction = CHAIN_DIRECTION_OR;
	}
	else {
		cc->direction = CHAIN_DIRECTION_AND;
	}
	cc->flags |= CHAIN_FLAG_NOT;
	if (cc->left) {
		flip_chain(cc->left);
	}
	if (cc->right) {
		flip_chain(cc->right);
	}
}

void reduce(flow_node * n, flow_graph * flow_nodes, py_instruction * inst,
	int * visited, flow_node * parent_left, cond_chain ** ochain, cond_chain ** congruent, cond_chain * top) {

	// asc here is the child that reaches the other child (desc)
	// if the asc node is the same as the desc from the parent, it stops
	pylog("reduce on %i, parent left is %i\n", n->initial_inst->off, parent_left ? parent_left->initial_inst->off : -1);
	set_visited(n, visited);

	flow_left_right_result result;
	flow_left_right_reachability(n, flow_nodes, &result);
	
	cond_chain * chain = new cond_chain();	
	chain->chain_top = top;
	(*ochain) = chain;
	chain->type = CHAIN_TYPE_COND;
	chain->node = n;
	pylog("reach %i, right %i, left %i\n", result.state,result.right ? result.right->begin_off : -1, result.left ? result.left->begin_off : -1);
	if (result.state != STATE_NO_PATH && result.state != STATE_NO_PATH_DESC &&
		result.state != STATE_PATH && parent_left && result.right == parent_left) {
		pylog("stop on parent left\n");
		chain->flags |= CHAIN_FLAG_ENDCHAIN;
		return;
	}

	if (n->final_inst->opcode == POP_JUMP_IF_FALSE || n->final_inst->opcode == JUMP_IF_FALSE_OR_POP) {
		// right is semantic and
		pylog("chain and\n");
		chain->direction = CHAIN_DIRECTION_AND;
	}
	if (n->final_inst->opcode == POP_JUMP_IF_TRUE) {
		// right is semantic or
		pylog("chain or\n");
		chain->direction = CHAIN_DIRECTION_OR;
	}
	int end_of_chain = 0;
	uint32 eoc_type = 0;
	pylog("result %i", result.state);
	if (result.state == STATE_PATH_INCONGRUENT) {
		py_assert(n->final_inst->opcode == POP_JUMP_IF_FALSE || n->final_inst->opcode == POP_JUMP_IF_TRUE ||
			n->final_inst->opcode == JUMP_IF_FALSE_OR_POP,
			"Invalid instruction on graph analysis");

		pylog("incongruent\n");
		

		cond_chain *c;

		pylog("right chain reduce %i\n", n->initial_inst->off);
		reduce(result.right, flow_nodes, inst, visited, result.left, &c, congruent,top ? top : chain);
		
		chain->right = c;
		pylog("right end on %i\n", n->initial_inst->off);
		if (*congruent) {
			cond_chain *cc = (*congruent);
			if (result.left == cc->left->node) {
				pylog("tops %i %i\n", cc->chain_top->node->initial_inst->off, chain->node->initial_inst->off);
				if (cc->chain_top == chain) {
					cc->flags |= CHAIN_FLAG_ENDCHAIN;
				}
			}
		}

		if (result.left == parent_left) {
			pylog("left same as parent %i\n", n->initial_inst->off);
			// no further analysis on this chain			
			return;
		}		

		if (*congruent) {
			cond_chain *cc = (*congruent);
			
			pylog("cc %i %i\n",result.left->initial_inst->off,cc->left->node->initial_inst->off);
			pylog("cc %i %i\n", result.right->initial_inst->off, cc->right->node->initial_inst->off);
			py_assert(cc->left->node != NULL && cc->right->node != NULL, "Invalid node on congruence");
			if (result.left == cc->left->node || result.right == cc->right->node || 
				result.left == cc->right->node || result.right == cc->left->node) {
				
				// block reached
				chain->left = new cond_chain();
				chain->left->node = result.left;
				chain->left->type = CHAIN_TYPE_BLOCK;
				chain->flags |= CHAIN_FLAG_STARTCHAIN;
				if (cc->chain_top == chain) {
					cc->flags |= CHAIN_FLAG_ENDCHAIN;	
								
				}				
				cc->endcount++;	
				pylog("congruence end %i\n", n->initial_inst->off);
				return;
			}
		}

		pylog("left chain reduce %i to %i\n", n->initial_inst->off,result.left->initial_inst->off);
				
		reduce(result.left, flow_nodes, inst, visited, parent_left, &c, congruent,NULL);

		chain->flags |= CHAIN_FLAG_STARTCHAIN;
		chain->left = c;
		chain->left->flags |= CHAIN_FLAG_ENDCHAIN;
		chain->left->endcount++;

	}
	else if (result.state == STATE_PATH) {
		// typical for ifs without else, might occur several times in the chains
		// check if right is pure conditional atom or stop
		pylog("path congruent %i\n", result.right->flags);
		py_assert(result.right != NULL,"Invalid nodes on reduce");
		if (result.right->flags & FLOW_FLAG_PURE_CONDITIONAL) {
			cond_chain * c;
			if (result.right != parent_left) {
				pylog("right chain reduce %i", result.right->initial_inst->off);
				reduce(result.right, flow_nodes, inst, visited, result.left, &c, congruent, top ? top : chain);
				pylog("attach right chain %i", c->node->initial_inst->off);
				chain->right = c;
			}
			else {
				pylog("parent stop\n");
			}

			if (*congruent) {
				cond_chain *cc = (*congruent);
				if (cc->flags & CHAIN_FLAG_NO_PATH) {
					if (result.left == cc->left->node) {
						pylog("tops %i %i\n", cc->chain_top->node->initial_inst->off, chain->node->initial_inst->off);
						if (cc->chain_top == chain) {
							cc->flags |= CHAIN_FLAG_ENDCHAIN;
						}
					}
				}
				if (cc->flags & CHAIN_FLAG_PATH) {
					if (result.right == cc->left->node) {
						pylog("tops %i %i\n", cc->chain_top->node->initial_inst->off, chain->node->initial_inst->off);
						if (cc->chain_top == chain) {
							cc->flags |= CHAIN_FLAG_ENDCHAIN;
						}
					}
				}
			}
			
		}
		else {
			end_of_chain = 1;
			eoc_type = CHAIN_FLAG_PATH;			
		}		
	}
	else if (result.state == STATE_NO_PATH || result.state == STATE_NO_PATH_DESC) {
		pylog("congruent\n");
		
		// typical for ifs with else, occurs only once at the chain end		
		// both children are the conditional exits
		end_of_chain = 1;
		if (result.state == STATE_NO_PATH) {
			eoc_type = CHAIN_FLAG_NO_PATH_NO_DESC;
			

		}
		else if (result.state == STATE_NO_PATH_DESC) {
			eoc_type = CHAIN_FLAG_NO_PATH;
		}
		else {
			py_assert(0, "No valid state on chain congruence");
		}

		if (result.flags & FLOW_LR_RESULT_LOOPED) {
			// in this case we do have an else, and according to the 
			// true/false on the instruction it looped, ie it is a 'continue'
			// statement
			pylog("one of the children looped");
			eoc_type |= CHAIN_FLAG_CONTINUE;
		}
	}

	if (end_of_chain) {
		pylog("end of chain");
		// end of conditional
		chain->right = new cond_chain();
		chain->right->node = result.right;
		chain->right->type = CHAIN_TYPE_BLOCK;
		chain->left = new cond_chain();
		chain->left->node = result.left;
		chain->left->type = CHAIN_TYPE_BLOCK;
		chain->flags |= CHAIN_FLAG_ENDCOND;
		chain->flags |= eoc_type;

		py_assert(*congruent == NULL, "Invalid congruent on block analysis");
		*congruent = chain;
		
	}	
	pylog("reduce end on %i", n->begin_off);
}

void build_chain_atom(source_atom_tree * atoms, source_atom * root, cond_chain * t) {
	
	source_atom * at = atoms->from_instruction(t->node->final_inst);	
	pylog("final inst from %i: %i", t->node->begin_off, t->node->final_inst->off);
	py_assert(at->inst->stack_referrals_sz > 0,"Unknown conditional construct");
	pylog("atom size %i", at->referenced_nodes.size);
	source_atom_tree_node * pnodes[128];
	//int rt = at->get_top_all_branches(pnodes);
	int rt = 0;
	int i;
	source_atom_tree_node * nx = earray_get(&at->referenced_nodes, 0, source_atom_tree_node*);
	
	while (nx) {
		if (nx->atom->type == SOURCE_ATOM_UNPACK_SEQUENCE) {
			for (i = 0; i < nx->atom->referenced_nodes.size; i++) {
				source_atom_tree_node * n1 = earray_get(&nx->atom->referenced_nodes, i, source_atom_tree_node*);
				while (n1->parent) {
					n1 = n1->parent;
				}
				pnodes[rt++] = n1;
			}
		}
		if (!nx->parent && rt == 0) {
			pnodes[rt++] = nx;
		}
		nx = nx->parent;
	}
	
	for (i = 0; i < rt; i++) {
		at = pnodes[i]->atom;
		if (at->inst) pylog("swap %i", at->inst->off);
		
		t->atom_top = at;
		pylog("new chain atom top %i", at->type);
		if (at->flags & ATOM_FLAG_COND_ELSE) {
			root->flags |= ATOM_FLAG_COND_ELSE;
		}
		
		atoms->node_root_swap(at, root);
		if (at->inst) {
			pylog("chain atom swap  %llX %X %i %s, node %i\n", root, at->flags, at->inst->off, at->inst->highlevel_name, t->node->begin_off);
		}
	}
	pylog("at type %i", at->type);
	py_assert(at->len > 0, "Invalid atom on chain");

	if (t->right && t->right->type != CHAIN_TYPE_BLOCK) {
		build_chain_atom(atoms,root,t->right);
	}
	if (t->left && t->left->type != CHAIN_TYPE_BLOCK) {
		build_chain_atom(atoms, root, t->left);
	}
	

}

source_atom * node_get_first_atom(flow_node * n,source_atom_tree * atoms) {
	source_atom * at = atoms->from_instruction(n->initial_inst);
	return at->get_tree_top();

}

int atom_binary_right_lookup(py_instruction * inst, source_atom_tree * atoms, int conditional) {
	int i,j;
	if (conditional) {
		py_assert(inst->stackbacks_sz > 1, "Invalid binary atom lookup");
		for (i = 0; i < inst->stack_referrals_sz; i++) {
			py_instruction * i1 = inst->stackbacks[0].stack_referrals[i];
			for (j = 1; j < inst->stackbacks_sz; j++) {
				if (inst->stackbacks[j].stack_referrals[i] != i1) {
					return i;
				}				
			}
		}
	}
	else {
		py_assert(0, "Unimplemented");
	}
	return -1;
}

int atom_inline_check(source_atom * cond, source_atom_tree * atoms, cond_chain * congruent,
	flow_node * desc) {

	pylog("next inline %i", desc->begin_off);
	source_atom * at = atoms->from_off(desc->begin_off);
	if (at->inst && at->inst->stackbacks_sz > 1) {
		pylog("inline conditional found at %i %s", at->inst->off, at->inst->highlevel_name);
		//swap node
		//set conditional atom on the referenced atom
		int idx = 0;
		if (at->type == SOURCE_ATOM_BINARYOPS) {
			idx = atom_binary_right_lookup(at->inst,atoms,1);
		}
		
		source_atom_data * pd = (source_atom_data*)at->data;
		
		py_assert(pd->watermark == WATERMARK && pd->replace_dest_atom, "Atom replace on invalid atom (%i)", at->type);

		cond_chain * cc = (cond_chain*)cond->data;
		cc->flags |= CHAIN_FLAG_INLINE;

		int i;
		for (i = 0; i < at->inst->stackbacks_sz; i++) {
			source_atom * a1 = atoms->from_instruction(at->inst->stackbacks[i].stack_referrals[idx]);
			cc->inline_atoms[at->inst->stackbacks_sz-(i+1)] = a1;
			atoms->node_root_swap(a1, cond);
		}		

		source_atom * old = pd->replace_dest_atom(pd,cond, idx);		
		
		atoms->node_root_swap(cond, at->get_tree_top());

		return 1;
	}
	return 0;

}


int is_node_excep_conditional(flow_node * n, source_atom_tree * atoms) {
	if (n->flags & FLOW_FLAG_EXCEPTION) {
		pylog("on except block");
		source_atom * at1 = atoms->from_instruction(n->final_inst);

		// check here if the condition on the except block is
		// an 'except compare' condition, if so, we have further excepts
		if (at1->type == SOURCE_ATOM_CONDJUMP) {
			source_atom * aref = (source_atom*)at1->data;

			if (aref->type == SOURCE_ATOM_COMPARE) {
				source_atom_compare * cp = (source_atom_compare*)aref->data;
				if (cp->op == PyCmp_EXC_MATCH) {
					pylog("except block is conditional");
					return 1;
				}
			}
		}
	}
	return 0;
}

void flow_apply(py_function * fn) {
	int i;
	pylog("flow_apply %s %llX\n",fn->name,fn);


	/*if (!strncmp(fn->name, "<genexpr>",9)) {
		pylog("Not examining flow for generator");
		return;
	}*/

	earray * fn_flow = &fn->flow_nodes->nodes;
	source_atom_tree * atoms = (source_atom_tree*)fn->atoms;
	
	int * visited = new int[fn->instruction_set_size];
	memset(visited, 0, sizeof(int)*fn->instruction_set_size);
	
	for (i = 0; i < fn->instruction_set_size; i++) {
		py_instruction * inst = &fn->instruction_set[i];
		source_atom * atom = atoms->from_instruction(inst);

		if (!atom->len) continue;
		
		if (visited[i]) continue;
		visited[i] = 1;
		
		flow_node * n = NULL;
		if (inst->to_jmp != -1) {

			int j;
			int found = 0;
			pylog("looking up %i\n", inst->off);
			for (j = 0; j < fn_flow->size; j++) {
				n = earray_get(fn_flow, j, flow_node*);

				if (n->final_inst == inst) {
					found = 1;
					break;
				}
			}
			int depth = n->depth;
			//py_assert(found, "Could not locate flow node, expect bad things");
			if (!found) {
				pylog("WARNING: Node is missing in graph for instruction %i %s\n", inst->off, inst->highlevel_name);
				continue;
			}
			if (inst->jmp_conditional == 1) {
				pylog("jmp_conditional at %i, depth %i, n is %i\n", inst->off, n->depth, n->initial_inst->off);

				if (inst->opcode == SETUP_FINALLY || inst->opcode == SETUP_EXCEPT) {
					pylog("finally/except block at %i\n",inst->off);
					// this is just a set up for the finally/except block, no conditional chain here
					int k;
					int closest = INT_MAX;
					int ck = -1;
					py_assert(n->outgoing.size == 2, "Invalid node on except block");
					for (k = 0; k < n->outgoing.size; k++) {
						flow_edge * e = earray_get(&n->outgoing, k, flow_edge*);
						flow_node * n1 = e->node;

						py_assert(n1->initial_inst != NULL, "Bad initial instruction on node");

						if (n1->initial_inst->off < n->initial_inst->off) {
							continue;
						}
						int d = n1->initial_inst->off - n->final_inst->off;
						if (d < closest) {
							closest = d;
							ck = k;
						}
					}

					py_assert(ck >= 0, "Invalid node on finally block");

					flow_node * try_block;
					flow_node * other_block;

					try_block = (earray_get(&n->outgoing, ck, flow_edge*))->node;
					other_block = (earray_get(&n->outgoing, !ck, flow_edge*))->node;
					source_atom * at;
					int tdepth1 = depth;
					pylog("try block at %i, other at %i", try_block->initial_inst->off,other_block->begin_off);
					if (try_block->initial_inst->opcode != SETUP_EXCEPT) {
						at = node_get_first_atom(try_block, atoms);
						pylog("set flag %i\n", at->inst ? at->inst->off : -1);
						at->flags |= ATOM_FLAG_TRY_BLOCK;
						tdepth1++;
					}

					at = node_get_first_atom(other_block, atoms);

					if (inst->opcode == SETUP_FINALLY) {
						at->flags |= ATOM_FLAG_FINALLY_BLOCK;
					}
					else {
						pylog("excep first %i %llX %X %i %i\n", at->type, at, at->flags, other_block->begin_off, at->inst ? at->inst->off : -1);
						other_block->flags |= FLOW_FLAG_EXCEPTION;
						at->flags |= ATOM_FLAG_EXCEPT_BLOCK;
					}

					pylog("try %i - %i\n", try_block->begin_off, other_block->begin_off);
					flow_node * c = flow_closest_descendant(fn->flow_nodes, try_block, other_block);
					if (c) {
						pylog("closest desc at %i %i %i -- %i %i -- %i %i\n", c->begin_off, try_block->begin_off, other_block->begin_off, tdepth1, depth + 1, c->depth, c->desired_depth);
					}
					flow_set_indent(fn, try_block, tdepth1, atoms, c,0);
					flow_set_indent(fn, other_block, depth + 1, atoms, c, 0);

					if (c) {
						flow_set_indent(fn, c, depth, atoms, NULL, 0);
					}


					continue;
				}

				cond_chain *c;
				cond_chain * ccongruent = NULL;
				pylog("starting reduce for new conditional");
				reduce(n, fn->flow_nodes, inst, visited, NULL, &c, &ccongruent, NULL);


				cond_chain * t = c;
				source_atom * at = atoms->extra_atom();
				pylog("pflags %X\n", ccongruent->flags);
				flow_node * cdesc = NULL;
				if (ccongruent->flags & CHAIN_FLAG_NO_PATH) {
					// else
					pylog("else");

					pylog("ccongruent node is %i", ccongruent->node->begin_off);					
					int target_depth = depth + 1;
					if (is_node_excep_conditional(ccongruent->node, atoms)) {
						ccongruent->left->flags |= FLOW_FLAG_EXCEPTION;
						source_atom * at1 = atoms->from_instruction(ccongruent->left->node->initial_inst);
						pylog("except atom %i", at1->inst ? at1->inst->off : -1);
						at1->get_tree_top()->flags |= ATOM_FLAG_EXCEPT_BLOCK;
						target_depth--;
					}
					else {
						ccongruent->left->node->flags |= FLOW_FLAG_ELSE_CONDITIONAL;
					}				

					source_atom * ax = atoms->from_instruction(ccongruent->left->node->initial_inst);

					source_atom_tree_node * p = earray_get(&ax->referenced_nodes, 0, source_atom_tree_node*);
					ax = p->get_tree_top();

					ax->flags |= ATOM_FLAG_COND_ELSE;
					pylog("path nodes %i %i\n", ccongruent->right->node->begin_off, ccongruent->left->node->begin_off);
					cdesc = flow_closest_descendant(fn->flow_nodes, ccongruent->left->node, ccongruent->right->node);
					pylog("indenting from no path with desc");
					flow_set_indent(fn, cdesc, depth, atoms, NULL,0);

					if (inst->opcode != JUMP_IF_FALSE_OR_POP && inst->opcode != JUMP_IF_TRUE_OR_POP) {
						pylog("cond set");
						flow_set_indent(fn, ccongruent->left->node, target_depth, atoms, cdesc, 0);
						flow_set_indent(fn, ccongruent->right->node, target_depth, atoms, cdesc, 0);
					}


				}
				else if (ccongruent->flags & CHAIN_FLAG_PATH || ccongruent->flags & CHAIN_FLAG_NO_PATH_NO_DESC) {
					pylog("setting indent %i at %i %i\n", depth + 1, ccongruent->right->node->initial_inst->off,
						ccongruent->left->node->initial_inst->off);

					pylog("from %i", ccongruent->node->begin_off);
					int j;
					
					if (flow_is_loop(ccongruent->node, ccongruent->right->node) == 1) {
						pylog("right congruent loop");
						flow_set_indent(fn, ccongruent->left->node, depth+1, atoms, NULL, 
							ccongruent->flags & CHAIN_FLAG_NO_PATH_NO_DESC);
					}
					else if (flow_is_loop(ccongruent->node, ccongruent->left->node) == 1) {
						pylog("left congruent loop");
						flow_set_indent(fn, ccongruent->right->node, depth + 1, atoms, ccongruent->left->node, 
							ccongruent->flags & CHAIN_FLAG_NO_PATH_NO_DESC);
					}
					else {
						// no else
						pylog("depth %i", depth);
						flow_set_indent(fn, ccongruent->left->node, depth, atoms, NULL, 
							ccongruent->flags & CHAIN_FLAG_NO_PATH_NO_DESC);

						source_atom * at1 = node_get_first_atom(ccongruent->node, atoms);
						pylog("ccongruent node is %i", ccongruent->node->begin_off);
						pylog("atom %i %i", at1->type, at1->inst ? at1->inst->off : -1);
						int tdepth = depth + 1;

						// check if the node is exception, and if the condition is an except compare
						if (is_node_excep_conditional(ccongruent->node,atoms)) {
							pylog("ccongruent is an except block");
							tdepth = depth;
							at1 = node_get_first_atom(ccongruent->left->node, atoms);
							

							//FIXME solve this at the translation
							//if (ccongruent->left->node->initial_inst->opcode != END_FINALLY) {
								//pylog("setting as except node %i", ccongruent->left->node->begin_off);
								//at1->flags |= ATOM_FLAG_EXCEPT_BLOCK;
							//}
						}
						pylog("tdepth %i", tdepth);
						flow_set_indent(fn, ccongruent->right->node, tdepth, atoms, ccongruent->left->node, ccongruent->flags & CHAIN_FLAG_NO_PATH_NO_DESC);
						pylog("preset %i %i\n", ccongruent->left->node->depth, ccongruent->left->node->initial_inst->off);
					}

					//printf("setting break on %i\n", ccongruent->left->node->initial_inst->off);
					//flow_set_break(ccongruent->left->node,atoms);
				}
				else {
					py_assert(0, "Invalid congruent block type %X", ccongruent->flags);
				}

				source_atom * a1 = atoms->from_instruction(t->node->final_inst);
				pylog("insert before %i %s\n", a1->inst->off, a1->inst->highlevel_name);
				
				int i;
				
				//py_assert(a1->referenced_nodes.size == 1, "Unknown overlap on atom formation %i",a1->referenced_nodes.size);
				source_atom_tree_node * tx = earray_get(&a1->referenced_nodes, 0, source_atom_tree_node*);
				pylog("new atom %i %s %llX\n", at->type,tx->atom->inst->highlevel_name,c->left);
				atoms->insert_before(tx->get_tree_top(), at);

				pylog("build chain at %i\n", n->initial_inst->off);
				build_chain_atom(atoms, at, t);
				pylog("root flags %X\n", at->flags);

				//printf("congruent %i %i\n", ccongruent->right->node->initial_inst->off, ccongruent->left->node->initial_inst->off);

				at->data = c;
				at->type = SOURCE_ATOM_CONDITIONAL;
				at->depth = n->depth;
				at->len = 1;

				// here we have to decide if the conditional is a regular if, or if it is 'inline', ie inside
				// another instruction

				if (ccongruent->flags & CHAIN_FLAG_NO_PATH) {
					atom_inline_check(at, atoms, ccongruent, cdesc);
				}

			}
		}
	}
	
	flow_node * nr = earray_get(fn_flow, 0, flow_node*);
	flow_queue q;
	q.add(nr);
	pylog("final indents");
	while (q.head) {
		flow_node * n = q.remove_first();
		if (n->desired_depth == -1) {
			//py_assert(flow_count_non_loop_incoming(n) < 2, "Invalid flow status (%i)",n->begin_off);
			if (n == nr) {
				flow_set_indent(fn, n, 0, atoms, NULL,0);
			}
			else {
				flow_node * n1 = earray_get(&n->incoming, 0, flow_node*);
				py_assert(n1->depth > -1, "Invalid flow status");
				flow_set_indent(fn, n, n1->depth, atoms, NULL,0);
			}
		}
		for (i = 0; i < n->outgoing.size; i++) {
			flow_edge * e = earray_get(&n->outgoing, i, flow_edge*);
			if (!(e->flags & FLOW_EDGE_FLAG_LOOP)) {
				q.add(e->node);
			}
		}
	}
	
	

	delete[] visited;
}

enum closed_block_type {
	CLOSED_BLOCK_WITH
};

#ifdef USE_INTERMEDIATE_LANGUAGE
#define WITH_BLOCK_DISP 1
#else
#define WITH_BLOCK_DISP 3
#endif 

void do_closed_block_indent(source_atom_tree * atoms, flow_graph * nodes, py_instruction * insts, py_instruction * inst, int type,
	source_atom_tree_node * ref) {
	pylog("do_closed_block_indent on %i",inst->off);
	flow_node * n = flow_get_node_from_instruction(nodes,inst);
	flow_queue q;
	py_assert(n != NULL, "Invalid node for instruction");
	uint32 off;
	flow_node * fin;

	if (type == CLOSED_BLOCK_WITH) {			
		off = inst->off + WITH_BLOCK_DISP + inst->arg;
		py_instruction * inst2 = &insts[off];
		pylog("look up node %i", off);
		fin = flow_get_node_from_offset(nodes,off);
		py_assert(fin != NULL, "Invalid node for instruction");
		pylog("final at %i %i\n",off,fin->begin_off);
		
	}
	
	source_atom_tree_node * t = ref;
	for(;;) {
		t->atom->depth++;
		
		if (t->atom && t->atom->inst) {
			pylog("atom st %i %i\n", t->atom->inst->off,t->atom->depth);
			if (t->atom->inst->off == off) {

				break;
			}
		}
		t = t->next;
		
	}
	return;
	q.add(n);
	int * visited = new int[nodes->nodes.size];
	memset(visited,0,sizeof(int)*nodes->nodes.size);
	pylog("%X\n", q.head);
	while (q.head) {
		flow_node * n1 = q.remove_first();
		pylog("with visit %i %i\n", n1->begin_off,visited[n1->idx]);
		if (visited[n1->idx]) continue;
		visited[n1->idx] = 1;
		if (type == CLOSED_BLOCK_WITH) {			
			n1->depth++;
			py_instruction * i1 = n1->initial_inst;
			while (i1 < n1->final_inst) {
				pylog("with set %i %s %i\n", i1->off,i1->highlevel_name,0);
				source_atom * at = atoms->from_instruction(i1);
				at->depth++;
				i1++;
			}
		}
		int i;
		int done = 0;
		for(i=0;i<n1->outgoing.size;i++) {
			flow_edge * e = earray_get(&n1->outgoing,i,flow_edge*);
			flow_node * nx = e->node;
			
			if (nx == fin) {
				continue;
			}
			
			q.add(nx);
		}
		
	}
	pylog("node %i %i\n",n->begin_off,n->depth);
	delete[] visited;
	
}

void chain_clear_else_flags(cond_chain * cc, source_atom_tree * atoms) {
	source_atom * at = node_get_first_atom(cc->node, atoms);
	at->flags &= !ATOM_FLAG_EXCEPT_BLOCK;
	if (cc->right) {
		chain_clear_else_flags(cc->right, atoms);
	}
	if (cc->left) {
		chain_clear_else_flags(cc->left, atoms);
	}
}

void chain_swap_conds(cond_chain * cc, source_atom * at, source_atom_tree * atoms) {
	py_instruction * inst = cc->node->final_inst;
	
	if (inst->opcode == JUMP_IF_FALSE_OR_POP || inst->opcode == JUMP_IF_TRUE_OR_POP ||
		inst->opcode == JUMP_FORWARD) {
		source_atom * atx = atoms->from_instruction(inst - 1);
		
	//	py_assert(atx->type == SOURCE_ATOM_STR || atx->type == SOURCE_ATOM_COMPARE, "Unknown conditional construct %i", atx->type);
		
		atoms->node_root_swap(atx, at);
		
	}
	
	if (inst->opcode == JUMP_FORWARD) {	
		// these chains are a bit different from usual if, and have
		// conditionals on non conditional jumps, since the conds
		// are used later
		cc->type = CHAIN_TYPE_COND;
	}
	if (cc->right) chain_swap_conds(cc->right, at, atoms);
	if (cc->left) chain_swap_conds(cc->left, at, atoms);
}

/**
 * Merge all atoms that can not be inferred in a top down analysis (ie 
 * they depend on atoms that come next. Only cases that do not depend
 * on graph analysis are merged here. Cases that do depend on graph
 * analysis are resolved in flow_apply().
 */
void merge_atoms(py_function * root) {
	py_instruction * inst;
	source_atom_tree * atoms = (source_atom_tree*)root->atoms;
	int i,j;
	pylog("started merging on %s\n",root->name);
	
	for (i = 0; i < root->instruction_set_size; i++) {
		inst = &root->instruction_set[i];
		
		if (inst->opcode == JUMP_IF_FALSE_OR_POP) {
			source_atom * at = atoms->from_instruction(inst);

			source_atom * aref = (source_atom*)at->data;
			
			source_atom * top = at->get_tree_top();
			pylog("JUMP_IF_FALSE_OR_POP chain at %i %i", at->get_tree_top()->type, inst->off);
			source_atom_tree_node * tx = earray_get(&at->referenced_nodes, 0, source_atom_tree_node*);
			int chained = 0;
			while (tx) {
				if (tx->atom->type == SOURCE_ATOM_SIMPLE_CHAIN) {
					// already chained
					pylog("already chained");
					chained = 1;
					break;
				}
				tx = tx->parent;
			}

			if (chained) {
				continue;
			}
			
			py_assert(top->type == SOURCE_ATOM_CONDITIONAL, "Invalid chain construct");

			cond_chain * cc = (cond_chain*)top->data;			
			
			chain_clear_else_flags(cc, atoms);

			cc->flags |= CHAIN_FLAG_SIMPLE;

			source_atom * ftarget;
			py_instruction * itarg;
			
			ftarget = atoms->from_off(inst->to_jmp);
			itarg = ftarget->inst;
			if (itarg->opcode == ROT_TWO) {
				itarg++;
				if (itarg->opcode == POP_TOP) {
					itarg++;
				}
				ftarget = atoms->from_instruction(itarg);
			}
			source_atom_tree_node * fnode = earray_get(&ftarget->referenced_nodes, 0, source_atom_tree_node*);
			
			chain_swap_conds(cc, ftarget->get_tree_top(),atoms);
			pylog("ftarg refs %i %i, %llX, %llX %llX", ftarget->referenced_nodes.size, ftarget->inst->off, ftarget, fnode, fnode->parent);

			pylog("itarg %i %i %s", itarg->stackbacks_sz,itarg->off,itarg->highlevel_name);
			if (itarg->stackbacks_sz) {
				for (j = 0; j < itarg->stackbacks_sz; j++) {
					int k;
					for (k = 0; k < itarg->stack_referrals_sz; k++) {
						source_atom * ax = atoms->from_instruction(itarg->stackbacks[j].stack_referrals[k]);
						pylog("%i", itarg->stackbacks[j].stack_referrals[k]->off);
						if (atoms->get_root_node(ftarget) != NULL) {
							atoms->node_root_swap(ax, ftarget);
						}
					}
				}
			}
			
			
			pylog("ftarg %i %i %i, %llX\n", ftarget->type, ftarget->get_tree_top()->type, ftarget->inst->off,fnode->parent);
			
			source_atom * extra = atoms->extra_atom();

			extra->type = SOURCE_ATOM_SIMPLE_CHAIN;
			extra->data = top;
			extra->len = 1;

			atoms->insert_before(top, extra);

			atoms->node_root_swap(top, extra);
			
			cc->extra_data = NULL;	
			
			
			source_atom * ax = atoms->from_instruction(cc->node->final_inst - 1);
			
			source_atom_compare * cm = (source_atom_compare*)ax->data;			
						
			source_atom_callfunction * c = (source_atom_callfunction*)ftarget->data;
			
			for (;;) {
				
				if (ftarget->type == SOURCE_ATOM_CALLFUNCTION) {
					cc->extra_data = ftarget;
				}
				else if (ftarget->type == SOURCE_ATOM_CONDITIONAL) {
					cc->extra_data = ftarget;
				}
				else if (ftarget->type == SOURCE_ATOM_RETURN) {
					cc->extra_data = (source_atom*)ftarget->data;
					ftarget->data = extra;
				}
				else if (ftarget->type == SOURCE_ATOM_STORE_VAR) {
					source_atom_store_val * v = (source_atom_store_val*)ftarget->data;
					//cc->extra_data = v->st_atom;				
					v->st_atom = extra;
				}
				else {
					
					fnode = fnode->parent;
					py_assert(fnode != NULL, "Unknown chain");
					ftarget = fnode->atom;
					
					
					py_assert(ftarget != NULL, "Unknown chain");
					continue;
					//py_assert(0, "Unimplemented chain %i %s", ftarget->type,ftarget->inst->highlevel_name);
				}
				break;
			}
			
			pylog("%llX %llX\n", ftarget, ftarget->get_tree_top());			
			
			atoms->node_root_swap(ftarget->get_tree_top(),extra);			
			
		}
		else if (inst->opcode == FOR_ITER) {
			pylog("for iter at %i %i",inst->off,inst->to_jmp);
			source_atom * at = atoms->from_instruction(inst);
			//py_assert(at->referenced_nodes.size == 1, "Unknown for construct");
			source_atom_tree_node * nx = earray_get(&at->referenced_nodes, 0, source_atom_tree_node*);
			source_atom * top = nx->get_tree_top();

			
			pylog("top atom is %i, %X", top->type,root->flags);
			if (top->type != SOURCE_ATOM_LOOP_START) {
				if (top->type == SOURCE_ATOM_STORE_VAR) {
					pylog("generator %i",top->inst->off);
					source_atom_tree_node * nt = earray_get(&top->referenced_nodes, 0, source_atom_tree_node*);
					source_atom * ax = nt->next->atom;

					if (ax->type == SOURCE_ATOM_POP) {
						ax = (source_atom*)ax->data;
					}
					ax = ax->get_tree_top();
					if (ax->type == SOURCE_ATOM_YIELD) {

						source_atom_generator_construct * ct = new source_atom_generator_construct();
						ct->expr = (source_atom*)ax->data;

						source_atom_store_val * sv = (source_atom_store_val*)top->data;
						sv->generator = ct;
						pylog("pygen %llX %i \n", sv, ax->type);
					}
					else if (ax->type == SOURCE_ATOM_CONDITIONAL) {
						/*source_atom_generator_construct * ct = new source_atom_generator_construct();
						ct->expr = (source_atom*)ax->data;

						cond_chain * sv = (cond_chain*)top->data;
						sv->generator = ct;*/
					}
					else {
						py_assert(0, "Unknown <genexpr> format (%i)",ax->type);
					}

				}				
				else {					
					int depth = top->depth;
					py_assert(nx->get_tree_top()->type == SOURCE_ATOM_CONDITIONAL, "Unknown for construct %i", nx->get_tree_top()->type);
					pylog("inline for at %i",inst->off);

					// for isn't in a typical loop, this is usually inline 'for'
					cond_chain * cc = (cond_chain*)nx->get_tree_top()->data;
					
					// next part is heuristical and looks for specific type of inline for construct
					source_atom_inline_for_construct * ct = new source_atom_inline_for_construct();
					flow_node * l = cc->right->node;

					source_atom * inner_storage;
					inner_storage = atoms->from_instruction(l->initial_inst);					
					
					py_assert(inner_storage->type == SOURCE_ATOM_STORE_VAR || inner_storage->type == SOURCE_ATOM_UNPACK_SEQUENCE,
						"Unknown for construct %i", inner_storage->type);
					pylog("inner_storage at %i", inner_storage->inst->off);
					//ct->var = inner_storage;
					source_atom_tree_node * n = NULL;
					int most = 0;
					pylog("number of ref nodes %i", inner_storage->referenced_nodes.size);
					ct->var_size = inner_storage->referenced_nodes.size;
					ct->var = new source_atom*[ct->var_size];

					if (inner_storage->type == SOURCE_ATOM_UNPACK_SEQUENCE) {
						source_atom_unpacked_sequence * us = (source_atom_unpacked_sequence*)inner_storage->data;
						py_assert(us->size == inner_storage->referenced_nodes.size, "Abnormal foriter construct");
						
					}

					if (inner_storage->referenced_nodes.size > 1) {
						source_atom_tree_node * n1;
						for (j = 0; j < inner_storage->referenced_nodes.size; j++) {
							n1 = earray_get(&inner_storage->referenced_nodes, j, source_atom_tree_node*);
							py_assert(n1->parent != NULL, "Invalid tree node construct");
							
							while (n1->parent && n1->parent->atom->type != SOURCE_ATOM_CONDITIONAL) {
								n1 = n1->parent;
							}
							if (n1->atom->inst->off > most) {
								most = n1->atom->inst->off;
								n = n1;
							}
							pylog("multi tree top %i", n1->atom->inst->off);
							atoms->node_root_swap(n1->atom, top);
							ct->var[j] = n1->atom;
							
						}
					}
					else {
						
						n = earray_get(&inner_storage->referenced_nodes, 0, source_atom_tree_node*);
						while (n->parent && n->parent->atom->type != SOURCE_ATOM_CONDITIONAL) {
							n = n->parent;
						}
						ct->var[0] = n->atom;
					}
					py_assert(n != NULL, "invalid tree nodes?");
					pylog("nref %i %i ", n->atom->inst->off,0);
					
					n = earray_get(&n->atom->get_tree_top()->referenced_nodes, 0, source_atom_tree_node*);
					n = n->next;					
					
					if (n->atom->inst) {
						pylog("%i %s\n", n->atom->inst->off, n->atom->inst->highlevel_name);
					}					

					while (n->atom->type == SOURCE_ATOM_CONDITIONAL) {
						ct->conditionals.add(n->atom);	
						cond_chain * c1 = (cond_chain*)n->atom->data;
						c1->flags |= CHAIN_FLAG_INLINE;
						n = n->next;						
					}


					ct->function = n->atom;
					n = n->next;					
					pylog("inline for body off %i, function is %i %i", n->atom->inst->off,ct->function->type,ct->function->inst->off);
					if (n->atom->type == SOURCE_ATOM_BINARYOPS) {
						n = n->next;
					}
					
					py_instruction * final_inst = &root->instruction_set[inst->to_jmp - 1];
					source_atom * af = atoms->from_instruction(final_inst);
					py_assert(af->type == SOURCE_ATOM_JUMP, "Unknown for construct (%i)", af->type);
					py_assert(af->referenced_nodes.size == 1, "Unknown for construct (%i)", af->referenced_nodes.size);
					source_atom_tree_node * nf = earray_get(&af->referenced_nodes, 0, source_atom_tree_node*);					
					py_assert(nf->prev != NULL, "Unknown for construct");
					ct->finalfunction = nf->prev->atom;
					l = cc->left->node;

					source_atom * a1 = atoms->from_instruction(l->initial_inst);
					pylog("initial inst %s %i -- %i", l->initial_inst->highlevel_name, l->initial_inst->off,l->initial_inst->stack_referrals_sz);
					

					if (l->initial_inst->stack_referrals_sz > 1) {
						// foriter is not technically part of referrals, so we search
						// what happens here is that these instructions (the storage) should
						// not be referring for_iter
						//FIXME fix this in the stack solver instead
						pylog("arg %i", l->initial_inst->stack_referrals[1]->off);
						source_atom_tree_node * ntop = earray_get(&top->referenced_nodes, 0, source_atom_tree_node*);
						if (a1->type == SOURCE_ATOM_BINARYOPS) {
							source_binary_op * b = (source_binary_op*)a1->data;
							
							b->op2 = ntop->prev->atom;
						}
						else {
							py_assert(a1->type == SOURCE_ATOM_CALLFUNCTION, "Unimplemented foriter variation %i", a1->type);
							source_atom_callfunction * cf = (source_atom_callfunction*)a1->data;
							cf->fn = ntop->prev->atom;
							atoms->node_root_swap(ntop->prev->atom, a1->get_tree_top());
						}
					}
					

					int f = 0;
					py_instruction * rev = earray_get(&inst->reverse_stack_referrals, 0, py_instruction*);
					source_atom * storage = NULL;
					pylog("rev %i %i", rev->off, a1->inst->off);
					storage = atoms->from_instruction(rev);
					
					pylog("top depth %i",top->depth);
					ct->storage = storage;				
					
					pylog("storage type %i, at %i", storage->type, storage->inst->off);
					
					/* FIXME the following sequence alters the righthand/arg/whatever from the caller
						to the conditional object with the inline for construct, problem here is each
						atom has a different arg to alter, so rethink this to avoid this long if/else 
						chain */

					source_atom_data * pd = (source_atom_data*)storage->data;
					py_assert(pd->watermark == WATERMARK, "Atom replace on invalid atom (%i)", storage->type);

					py_assert(storage->inst != NULL, "Invalid inst on inline for storage");
					int ff = 0;
					for (j = 0; j < storage->inst->stack_referrals_sz; j++) {

					}

					pd->replace_dest_atom(pd,top, 0); // FIXME for binary/other types of ops need to find the correct index

					if (storage->type == SOURCE_ATOM_RETURN) {
						source_atom * val = (source_atom*)ct->storage->data;
						py_assert(val->type == SOURCE_ATOM_FORITER, "Unknown inline for construct");
						source_atom * sval = (source_atom*)val->data;
						if (sval->type == SOURCE_ATOM_STR) {
							source_atom_str * st = (source_atom_str*)sval->data;
							if (!strcmp(st->bytes, ".0")) {
								pylog("setting inline arg on return");
								ct->flags |= SOURCE_ATOM_FLAG_INLINEFOR_ARG0;								
							}
						}
						storage->data = top;
						
					}
					else if (storage->type == SOURCE_ATOM_STORE_SLICE) {
						source_atoms_store_slice * sl = (source_atoms_store_slice*)storage->data;
						pylog("set sdest %i", top->type);
						sl->dest = top;
					}
					else if (storage->type == SOURCE_ATOM_STORE_VAR) {
						source_atom_store_val * sl = (source_atom_store_val*)storage->data;
						sl->st_atom = top;
					}
					else if (storage->type == SOURCE_ATOM_CALLFUNCTION) {
						source_atom_callfunction * cf = (source_atom_callfunction*)storage->data;
						pylog("setting top %i", top->type);
						if (cf->varg_count > 0) {
							cf->vargs[0] = top;
						}
						else if (cf->va) {
							cf->va = top;
						}
						else if (cf->kw) {
							cf->kw = top;
						}
						
					}
					else if (storage->type == SOURCE_ATOM_GETITER) {
						storage->data = top;
					}
					else if (storage->type == SOURCE_ATOM_STORE_ATTR) {
						source_atom_store_attr * st = (source_atom_store_attr*)storage->data;
						st->st_atom = top;
					}
					else if (storage->type == SOURCE_ATOM_BINARYOPS) {
						source_binary_op * b = (source_binary_op*)storage->data;
						// find which side
						py_assert(storage->inst->stack_referrals_sz == 2, "Invalid BINARY operation");
						int ff = 0;
						for (j = 0; j < storage->inst->stack_referrals_sz; j++) {
							py_instruction * iref = storage->inst->stack_referrals[j];
							if (iref->off == inst->off) {
								ff = 1;
								pylog("binary storage at %i, %i",j,storage->inst->off);
								if (j == 0) {									
									b->op1 = top;
								}
								else {
									b->op2 = top;
								}
							}
						}
						py_assert(ff == 1, "Binary storage not found");
						
					}
					else {
						py_assert(0, "Unimplemented for iter storage %i",storage->type);
					}
					

					atoms->node_root_swap(ct->function, top);
					atoms->node_root_swap(ct->finalfunction, top);
					ct->pexec = (source_atom*)at->data;
					
					//atoms->node_root_swap(ct->storage, top);					
					pylog("head %i \n", atoms->root_head->atom->type);
					cc->lambda = ct;
					int j;
					for (j = 0; j < ct->conditionals.size; j++) {
						source_atom * at = earray_get(&ct->conditionals, j, source_atom*);
						atoms->node_root_swap(at, top);
					}
					top->depth = depth;

					pylog("head %llX %llX \n", top, storage->get_tree_top());
					pylog("pstorage %i", storage->get_tree_top()->type);
					atoms->node_root_swap(top, storage->get_tree_top());

					py_instruction * inst2 = inst;
					while (inst2->opcode != CONTINUE_LOOP) {
						inst2++;
						if (inst2 >= root->instruction_set + root->instruction_set_size) {
							inst2 = NULL;
							break;
						}
					}
					if (inst2) {
						at = atoms->from_instruction(inst2);

						at->type = SOURCE_ATOM_DUMMY;
					}
					
					pylog("inline for - conditionals: %i, storage type: %i, storage inst: %i %s, finalfunction type: %i, "
						 "finalfunction inst: %i %s ",
						ct->conditionals.size,
						ct->storage->type,
						ct->storage->inst ? ct->storage->inst->off : -1,
						ct->storage->inst ? ct->storage->inst->highlevel_name : "none",
						ct->finalfunction->type,
						ct->finalfunction->inst ? ct->finalfunction->inst->off : -1,
						ct->finalfunction->inst ? ct->finalfunction->inst->highlevel_name : "none");
					
						
				}
			}
			else {
				pylog("already in loop");
			}
			
		}
		else if (inst->opcode == SETUP_LOOP) {
			
			pylog("SETUP_LOOP");
			source_atom * at = atoms->from_instruction(inst);
			py_assert(at->referenced_nodes.size > 0,"Bad atom on setup loop");
			source_atom_tree_node * n = earray_get(&at->referenced_nodes, 0, source_atom_tree_node*);
			
			py_assert(n->next != NULL, "Unknown loop construct");
			source_atom * at2 = n->next->atom;

			pylog("setting up loop %i %s %i\n", at2->inst ? at2->inst->off : -1, at2->inst ? at2->inst->highlevel_name : "null",at->type);
			
			// a while loop
			if (at2->type != SOURCE_ATOM_CONDITIONAL) {			
				pylog("tojmp %i", inst->loop_data);
				py_instruction * pinst = root->instruction_set;
				py_instruction * loop_end = NULL;
				printf("loop data %i\n", inst->loop_data);
				while (pinst < root->instruction_set + root->instruction_set_size) {
				
					if (pinst->off == inst->loop_data) {
						loop_end = pinst - 1;
						break;
					}
					pinst++;
				}				
				
				while (loop_end->opcode != JUMP_ABSOLUTE && loop_end->opcode != CONTINUE_LOOP) {
					loop_end--;
					py_assert(loop_end != inst, "Loop end not found");
				}

				py_assert(loop_end != NULL, "Bad loop end");

				source_atom * ax = atoms->from_instruction(loop_end);
				ax->data = (void*)1;

				pylog("loop end at %i %i", loop_end->off, loop_end->to_jmp);
				source_atom * atbase = atoms->from_off(loop_end->to_jmp);
				pylog("at %i %i, offset: %i", atbase->type, atbase->get_tree_top()->type,atbase->inst->off);


				//py_assert(0, "Bad atom on loop start %i %s %i", at2->type, at2->inst->highlevel_name);
				at2 = atbase->get_tree_top();

			}	

			if (at2->type != SOURCE_ATOM_CONDITIONAL) {	
				
				// an infinite loop
				at2 = atoms->extra_atom();
				atoms->insert_before(at,at2);
				int loop_end = inst->loop_data;
				pylog("infinite loop %i",loop_end);
				at2->depth = at->depth;
				atoms->node_root_swap(at, at2);
				at2->type = SOURCE_ATOM_CONDITIONAL_LOOP;
				at2->data = NULL;
				// we now force indent all the loop ahead
				py_instruction * inst2 = inst + 1;
				source_atom * last = NULL;
				while (inst2->off < loop_end) {
					source_atom * ax = atoms->from_instruction(inst2);
					ax = ax->get_tree_top();
					if (ax != last) {
						ax->depth++;
					}
					last = ax;
					inst2++;
				}
				

			}
			else {
				cond_chain * cc = (cond_chain*)at2->data;

				at2->depth = at->depth;
				atoms->node_root_swap(at2, at);

				pylog("atom loop at %i %i %i %i\n", at->type, at2->type, at->depth, cc->atom_top->type);
				at->data = at2;
				at2->type = SOURCE_ATOM_CONDITIONAL_LOOP;
			}
			
		}
		else if (inst->opcode == SETUP_WITH) {
			source_atom * at = atoms->from_instruction(inst);			
			
			py_assert(at->referenced_nodes.size == 1, "Unknown overlap on WITH");
			
			source_atom_tree_node * n = earray_get(&at->referenced_nodes, 0, source_atom_tree_node*);
			while (n->parent) {
				n = n->parent;
			}
			pylog("parent node indent %i\n", n->atom->depth);
			py_assert(n->atom->type == SOURCE_ATOM_STORE_VAR || n->atom->type == SOURCE_ATOM_POP, "Unknown with block type (%i)",n->atom->type);

					
			source_atom * w = atoms->extra_atom();
			
			atoms->insert_before(n->atom, w);
			source_atom_with * ww = new source_atom_with();
			ww->with = inst;
			w->data = ww;
			ww->origin = n->atom;
			ww->expr = (source_atom*)at->data;
			w->type = SOURCE_ATOM_WITH_BLOCK;

			atoms->node_root_swap(n->atom, w);
			
			atoms->node_root_swap((source_atom*)at->data, w);			
			atoms->node_root_swap(at, w);
		}
	}
	pylog("second pass\n");
	int * visited = new int[root->instruction_set_size];
	memset(visited, 0, sizeof(int)*root->instruction_set_size);
	
	for (i = 0; i < root->instruction_set_size; i++) {
		if (visited[i]) continue;
		inst = &root->instruction_set[i];
		
		visited[i] = 1;
		if (inst->opcode == SETUP_WITH) {
			pylog("Creating WITH group");
			source_atom * at = atoms->from_instruction(inst);
			source_atom_tree_node * n = earray_get(&at->referenced_nodes, 0, source_atom_tree_node*);
			
			while (n->parent) {
				n = n->parent;
			}			
			
			source_atom_tree_node * t = n;
			source_atom * p = atoms->extra_atom();
			atoms->insert_before(n->atom, p);			
			
			p->type = SOURCE_ATOM_WITH_BLOCK_GROUP;
			earray  * withs = new earray();
			source_atom * last;
			while (t->atom->type == SOURCE_ATOM_WITH_BLOCK) {
				pylog("swap\n");
				source_atom * w = t->atom;
				source_atom_with * ww = (source_atom_with*)w->data;
				last = w;
				t = t->next;
				withs->add(w);
				atoms->node_root_swap(w, p);
				visited[ww->with->idx] = 1;
				
			}
			source_atom_tree_node * pp = earray_get(&p->referenced_nodes, 0, source_atom_tree_node*);
			
			// find initial and final node of with block
			do_closed_block_indent(atoms,root->flow_nodes,root->instruction_set, inst,CLOSED_BLOCK_WITH,pp);
			pylog("with group size %i\n", withs->size);
			p->data = withs;
		}
	}

	delete[] visited;
}



/**
 * 'Beautifies' source, ie searches for known building blocks and
 * replace atoms with more usual python syntax
 */
void source_beautifier(py_function * root) {

}

void gen_prepare_function(py_function * fn) {
	gen_source_function(fn);

	flow_apply(fn);
	merge_atoms(fn);

	source_beautifier(fn);
	pylog("gen finished for %s", fn->name);
}

void gen_source(py_function * root, source_gen_out_buf * out) {
	
	gen_prepare_function(root);

	gen_print_source(root, out, 0);
}

/* actual source printing functions */


static char * gen_opcode_str[16] = { 0, };
static char * gen_binary_opcode[128] = { 0, };
static char gen_inplace_opcode[128] = { 0, };


void init_gen_print() {
	gen_opcode_str[PyCmp_LT] = "<";	
	gen_opcode_str[PyCmp_LE] = "<=";
	gen_opcode_str[PyCmp_EQ] = "==";
	gen_opcode_str[PyCmp_NE] = "!=";
	gen_opcode_str[PyCmp_GT] = ">";
	gen_opcode_str[PyCmp_GE] = ">=";
	gen_opcode_str[PyCmp_IN] = "in";
	gen_opcode_str[PyCmp_NOT_IN] = "not in";
	gen_opcode_str[PyCmp_IS] = "is";
	gen_opcode_str[PyCmp_IS_NOT] = "is not";
	gen_opcode_str[PyCmp_EXC_MATCH] = "=====";
	gen_opcode_str[PyCmp_BAD] = "----";

	memset(gen_inplace_opcode, 0, sizeof(gen_inplace_opcode));
	memset(gen_binary_opcode, 0, sizeof(gen_binary_opcode));
	gen_binary_opcode[BINARY_ADD] = "+";
	gen_binary_opcode[BINARY_MULTIPLY] = "*";
	gen_binary_opcode[BINARY_DIVIDE] = "/";
	gen_binary_opcode[BINARY_SUBTRACT] = "-";
	gen_binary_opcode[BINARY_MODULO] = "%";
	gen_binary_opcode[BINARY_RSHIFT] = ">>";
	gen_binary_opcode[BINARY_AND] = "&";
	gen_binary_opcode[BINARY_FLOOR_DIVIDE] = "//";
	gen_binary_opcode[BINARY_LSHIFT] = "<<";
	gen_binary_opcode[BINARY_POWER] = "**";
	

	

	gen_inplace_opcode[INPLACE_ADD] = '+';
	gen_inplace_opcode[INPLACE_SUBTRACT] = '-';
	
}


void gen_print_str_data(source_atom_str * st, source_gen_out_buf * out) {
	
	if (st->type == TYPE_STRING) {		
		if (st->subtype == SOURCE_STR_CONST) {
			char tmp[4096];
			
			escape_regular_string(tmp,st->bytes);
			out->bprintf("'%s'", tmp);
		}
		else if (st->subtype == SOURCE_STR_NAME) {			
			out->bprintf("%s", st->bytes);
		}
		else {
			py_assert(0, "Unknown str subtype");	
		}
	}
	else if (st->type == TYPE_STRINGREF) {
	}
	else if (st->type == TYPE_UNICODE) {	
		// unicode
		char tmp[4096];
		escape_regular_string(tmp, st->bytes);
		
		out->bprintf("u'%s'", tmp);
	}
	else {
		py_assert(0, "Invalid str const (%i)",st->type);
	}
}

void print_atom_conditional(source_atom * atom, source_gen_out_buf * out, source_atom_tree * atoms) {
	source_atom * cond = atom;
	if (atom->type == SOURCE_ATOM_CONDJUMP) {
		cond = (source_atom *)atom->data;		
	}
	out->add_space_if_none();
	
	gen_print_atom(cond, out, atoms);

	out->add_space_if_none();
	
	
}

int print_atom_chain(cond_chain * t, source_gen_out_buf * out, source_atom_tree * atoms, int chain_st) {
	
	source_atom * at = atoms->from_instruction(t->node->final_inst);	
	int flagret = 0;
	py_assert(at->type == SOURCE_ATOM_CONDJUMP || at->type == SOURCE_ATOM_JUMP, 
		"Invalid atom on conditional block %i",at->type);

	if (at->type == SOURCE_ATOM_JUMP) {
		at = atoms->from_instruction(t->node->final_inst-1);
	}

	if (t->flags & CHAIN_FLAG_STARTCHAIN) {
		out->add_space_if_none();
		out->bprintf("(");
		
	}

	if (t->flags & CHAIN_FLAG_NOT) {
		out->add_space_if_none();
		out->bprintf("not");
	}
	else if (t->flags & CHAIN_FLAG_ENDCOND && t->direction == CHAIN_DIRECTION_OR) {
		// compiler is a smartass here
		out->add_space_if_none();
		out->bprintf("not");
	}

	print_atom_conditional(at, out, atoms);
	
	if (t->flags & CHAIN_FLAG_ENDCHAIN) {
		int i;
		
		for(i=0;i<t->endcount;i++) {
			out->bprintf(")");
			
		}
	}
	
	if (t->right && t->right->type == CHAIN_TYPE_COND) {
		if (t->direction == CHAIN_DIRECTION_AND) {
			out->bprintf("and");
		}
		else {
			out->bprintf("or");
		}
		flagret |= print_atom_chain(t->right,out,atoms,0);
	}

	if (t->left && t->left->type == CHAIN_TYPE_COND) {
		int ch_st = 0;
		if (t->direction == CHAIN_DIRECTION_AND) {
			out->bprintf("or");
			ch_st = 1;
		}
		else {
			out->bprintf("and");
		}
		flagret |= print_atom_chain(t->left, out, atoms, ch_st);
	}

	return flagret |= (t->flags&CHAIN_FLAG_CONTINUE);
		
}

void gen_print_foriter(source_atom * atom, source_atom * foriter, source_gen_out_buf * out,
	 source_atom_tree * atoms, char * mexpr) {
	
	py_assert(atom->type == SOURCE_ATOM_STORE_VAR || atom->type == SOURCE_ATOM_UNPACK_SEQUENCE, 
		"Bad foriter print called %i",atom->type);

	if (atom->type == SOURCE_ATOM_STORE_VAR) {
		source_atom_store_val * sv = (source_atom_store_val*)atom->data;
		mexpr = sv->var;
	}
	
	py_assert(mexpr != NULL, "Invalid expression for FORITER");
	
	source_atom * getiter = (source_atom*)foriter->data;
	py_assert(getiter->type == SOURCE_ATOM_GETITER, "Bad foriter print called %i", getiter->type);

	source_atom * cfn = (source_atom*)getiter->data;
	
	if (cfn->type == SOURCE_ATOM_CALLFUNCTION) {
		source_atom_callfunction * f = (source_atom_callfunction*)cfn->data;
		
		out->bprintf("for %s in ", mexpr);
		gen_print_atom(cfn, out, atoms);

		out->bprintf(":");
	}
	else if (cfn->type == SOURCE_ATOM_LOAD_ATTR || cfn->type == SOURCE_ATOM_STR 
		|| cfn->type == SOURCE_ATOM_TUPLE || cfn->type == SOURCE_ATOM_LIST || 
		cfn->type == SOURCE_ATOM_BINARYOPS || cfn->type == SOURCE_ATOM_CONDITIONAL ||
		cfn->type == SOURCE_ATOM_SLICE_W || cfn->type == SOURCE_ATOM_TUPLECONST) {
		out->bprintf("for %s in ", mexpr);
		gen_print_atom(cfn, out, atoms);
		out->bprintf(":");
	}
	else {
		py_assert(0, "Unknown FORITER %i",cfn->type);
	}

}

void gen_print_lambda(source_atom_inline_for_construct * lambda, source_gen_out_buf * out, source_atom_tree * atoms) {
	// TODO merge this and gen_print_foriter and general atom printing for getiter and foriter, this is too confusing
	
	pylog("printing inline for");

	source_atom_store_val * v = (source_atom_store_val*)lambda->storage->data;	
	
	
	if (lambda->finalfunction->type == SOURCE_ATOM_SET_ADD) {
		out->bprintf("{");
	}
	else if (lambda->finalfunction->type == SOURCE_ATOM_LIST_APPEND) {
		out->bprintf("[");
	}
	else if (lambda->finalfunction->type == SOURCE_ATOM_MAP_ADD) {
		out->bprintf("{");

		source_atom_keyval * kv = (source_atom_keyval*)lambda->finalfunction->data;
		pylog("x %llX", kv);
		gen_print_atom(kv->key, out, atoms);
		out->bprintf(":");
	}
	else if (lambda->finalfunction->type == SOURCE_ATOM_POP) {
		source_atom * at = (source_atom*)lambda->finalfunction->data;
		pylog("sub type %i", at->type);
		py_assert(at->type == SOURCE_ATOM_YIELD, "Unknown inline for construct");
		// generator inline for
		source_atom * gen = (source_atom*)at->data;
		pylog("gen type %i", gen->type);
		gen_print_atom(gen, out, atoms);

	}
		
	gen_print_atom(lambda->function, out, atoms);
	out->add_space_if_none();

	out->bprintf("for ");
	int i;
	for (i = 0; i < lambda->var_size; i++) {
		source_atom * v = lambda->var[i];
		
		py_assert(v->type == SOURCE_ATOM_STORE_VAR, "Unimplemented foriter structure");
		source_atom_store_val * vx = (source_atom_store_val*)v->data;
		out->bprintf("%s", vx->var);
		if (i < lambda->var_size - 1) {
			out->bprintf(",");
		}
	}
	out->add_space_if_none();
	
	out->bprintf("in ");

	pylog("inline for flags %X", lambda->flags);

	if (lambda->flags & SOURCE_ATOM_FLAG_INLINEFOR_ARG0) {
		py_assert(atoms->caller != NULL, "Invalid inline for construct");
		gen_print_atom(atoms->caller->vargs[0], out, atoms->caller_atoms);
	}	
	else {
		source_atom * orig = (source_atom*)v->st_atom->data;
		gen_print_atom(lambda->pexec, out, atoms);
	}

	if (lambda->conditionals.size > 0) {
		int i;
		for (i = 0; i < lambda->conditionals.size; i++) {
			source_atom * c = earray_get(&lambda->conditionals, i, source_atom*);
			gen_print_atom(c, out, atoms);
		}
	}

	if (lambda->finalfunction->type == SOURCE_ATOM_SET_ADD) {
		out->bprintf("}");
	}
	else if (lambda->finalfunction->type == SOURCE_ATOM_LIST_APPEND) {
		out->bprintf("]");
	}
	else if (lambda->finalfunction->type == SOURCE_ATOM_MAP_ADD) {
		out->bprintf("}");
	}
}


void gen_print_genexpr_function(source_atom_generator_construct * generator, source_gen_out_buf * out, source_atom_tree * atoms) {
	//heuristical genexpr print
	gen_print_atom(generator->expr, out, atoms);
}

void gen_print_lambda_function(source_atom * atom, source_gen_out_buf * out, source_atom_tree * atoms) {
	source_atom_function * f = (source_atom_function*)atom->data;
	
	out->bprintf("lambda ");
	int i;
	for (i = 0; i < f->func->argcount; i++) {
		if (!strcmp(f->func->arg_names[i], ".0")) {
			int j;			
			out->bprintf("(");
			for (j = i+1; j < i+3; j++) {
				out->bprintf("%s", un_resolve_str(f->func->code->varnames->data[j]));
				if (j < i + 2) {
					out->bprintf(",");
				}
			}
			out->bprintf(")");
			continue;
		}
		out->bprintf("%s", f->func->arg_names[i]);
		if (i < f->func->argcount - 1) {
			out->bprintf(",");
		}
	}
	out->add_space_if_none();
	out->bprintf(":");

	py_instruction * final = &f->func->instruction_set[f->func->instruction_set_size - 1];
	source_atom * at = ((source_atom_tree*)f->func->atoms)->from_instruction(final);
	pylog("%i", final->off);
	py_assert(at->type == SOURCE_ATOM_RETURN,"Unknown lambda construct %i",at->type);

	source_atom * ret_content = (source_atom*)at->data;
	gen_print_atom(ret_content, out, ((source_atom_tree*)f->func->atoms));

}

void gen_special_unpack_clear(py_instruction * inst, source_atom_tree * atoms) {
	source_atom * at = atoms->from_instruction(inst);
	
	py_assert(at != NULL, "No atom for unpack");
	at->type = SOURCE_ATOM_DUMMY;
	int i;
	
	for (i = 0; i < inst->reverse_stack_referrals.size; i++) {
		
		py_instruction * xinst = earray_get(&inst->reverse_stack_referrals, i, py_instruction*);
		
		gen_special_unpack_clear(xinst,atoms);
	}
}

void gen_print_special_unpack(char * name, source_atom_function* f, source_gen_out_buf * out, source_atom_tree * atoms) {
	// here we get the first few instructions and unpack the arg
	py_instruction * inst = &f->func->instruction_set[0];
	source_atom_tree * fatoms = (source_atom_tree*)f->func->atoms;
	
	gen_special_unpack_clear(inst, fatoms);
	pylog("special unpack");
	un_tuple * tuple = disasm_build_unpacked_tuple(inst,f->func);
	source_atom at2;
	at2.type = SOURCE_ATOM_TUPLECONST;
	source_atom_tupleconst * c = new source_atom_tupleconst();
	at2.data = c;
	c->tuple = tuple;
	gen_print_atom(&at2, out, fatoms);
	delete c;
}

/*
 * Print an atom as a ready to use source. It is important here
 * to provide the top level atom for a line (determined by lens
 * and refs). If a lower level atom is provided the line will 
 * not make sense in this source.
 */
void gen_print_atom(source_atom * atom, source_gen_out_buf * out, source_atom_tree * atoms) {
	
	switch (atom->type) {
	case SOURCE_ATOM_GETITER: {
		//out->bprintf("getiter ");
		source_atom * at = (source_atom*)atom->data;
		gen_print_atom(at, out, atoms);
		break;
	}
	case SOURCE_ATOM_INT64: {
		source_atom_int64 * i = (source_atom_int64*)atom->data;
		out->bprintf("%lli ", i->val);
		break;
	}
	case SOURCE_ATOM_FORITER: {
		
		out->bprintf("for ");
		
		source_atom * at = (source_atom*)atom->data;
		gen_print_atom(at, out, atoms);
		break;
	}
	case SOURCE_ATOM_PRINT: {
		out->bprintf("print(");
		source_atom * p = (source_atom*)atom->data;
		gen_print_atom(p,out,atoms);
		out->bprintf(")");
		break;	
	}
	case SOURCE_ATOM_PRINTNEWLINE: {
		if (atom->data) {
			source_atom * p = (source_atom*)atom->data;
			gen_print_atom(p,out,atoms);
		}
		break;	
	}
	case SOURCE_ATOM_INPLACEOPS: {
		source_inplace_op * sb = (source_inplace_op*)atom->data;
		out->bprintf("(");
		gen_print_atom(sb->op1, out, atoms);
		int cb = gen_inplace_opcode[sb->type];
		out->add_space_if_none();
		py_assert(cb > 0, "Unimplemented INPLACE op %s", opcode_to_str(sb->type));
		out->bprintf("%c", cb);
		out->add_space_if_none();
		
		gen_print_atom(sb->op2, out, atoms);
		out->bprintf(")");

		break;
	}
	case SOURCE_ATOM_BINARYOPS: {
		source_binary_op * sb = (source_binary_op*)atom->data;

		source_atom * atom1 = sb->op2;
		source_atom * atom2 = sb->op1;

		if (atom->flags & ATOM_FLAG_MULTISTACK) {
			// we have multiple paths for this atom, search for a conditional here
			source_atom * pcond = atom->get_tree_top();
			source_atom_tree_node * n = earray_get(&atoms->from_off(9)->referenced_nodes, 0, source_atom_tree_node*);
		//	py_assert(n->prev != NULL, "Invalid multistack construct");
			pylog("%i", n->parent->parent->atom->inst);
		}

		if (sb->type == BINARY_SUBSCR) {
			gen_print_atom(atom1, out, atoms);
			out->bprintf("[");
			gen_print_atom(atom2, out, atoms);
			out->bprintf("]");
			break;
			
		}

		out->add_space_if_none();
		if (!(sb->flags & SOURCE_BINARY_NO_PARENTHESIS)) {
			out->bprintf("( ");
		}
		
		gen_print_atom(atom1,out,atoms);
		
		out->add_space_if_none();
		
		char * cb = gen_binary_opcode[sb->type];
		py_assert(cb != NULL, "Binary op unknown %s", opcode_to_str(sb->type));
		out->bprintf("%s",cb);
		out->add_space_if_none();
		
		gen_print_atom(atom2, out, atoms);


		out->add_space_if_none();
		if (!(sb->flags & SOURCE_BINARY_NO_PARENTHESIS)) {
			out->bprintf(")");
		}
		break;
	}
	case SOURCE_ATOM_FUNCTION: {
		source_atom_function * f = (source_atom_function*)atom->data;
		
		if (f->flags & SOURCE_FUNCTION_FLAG_LAMBDA) {
			gen_print_lambda_function(atom, out, atoms);
			break;
		}

		if (f->flags & SOURCE_FUNCTION_FLAG_GENERATOR) {			
			pylog("deferring generator def");
			break;
		}

		if (f->flags & SOURCE_FUNCTION_FLAG_SETCOMP) {
			pylog("deferring setcomp def");
			break;
		}

		if (f->flags & SOURCE_FUNCTION_FLAG_DICTCOMP) {
			pylog("deferring dictcomp def");
			break;
		}

		py_assert(f->func->atoms != NULL, "Function has no atoms? %s", f->fnname);

		if (f->annotation[0]) {
			int depth = out->cur_depth;
			out->bprintf("@%s", f->annotation);
			out->flush();
			out->set_depth(depth);
		}

		out->bprintf("def %s(", f->fnname);
		int defarg_idx = f->func->argcount - f->defargs_sz;
		int kdefarg = f->defargs_sz-1;
		pylog("defarg_idx %s %i %i", f->fnname, defarg_idx, f->func->argcount);
		int i;
		for (i = 0; i < f->func->argcount; i++) {			
			char * name = f->func->arg_names[i];
			
			if (name[0] == '.') {
				// special arg, need to unpack
				gen_print_special_unpack(name, f,out,atoms);
			}
			else {
				out->bprintf("%s", name);
			}
			
			if (i == defarg_idx) {
				out->bprintf("=");
				
				gen_print_atom(f->defargs[kdefarg--], out, atoms);
				defarg_idx++;				
			}
			if (i < f->func->argcount - 1) {
				out->bprintf(",");
			}			
		}
		if (f->func->var_arg) {
			if (i > 0) {
				out->bprintf(",");
			}
			out->bprintf("*%s", f->func->var_arg);
		}
		if (f->func->kw_arg) {
			out->bprintf(",**%s", f->func->kw_arg);
		}

		out->bprintf("):");
		int depth = out->cur_depth;
		out->flush();

		gen_print_source(f->func, out, depth + 1);
		break;
	}
	case SOURCE_ATOM_STORE_VAR: {
		source_atom_store_val * sv = (source_atom_store_val*)atom->data;
		source_atom* sva = sv->st_atom;
		
		if (sv->generator) {			
			gen_print_genexpr_function(sv->generator,out,atoms);
			out->add_space_if_none();
			
			out->bprintf("for %s ", sv->var);			
			break;
		}

		if (sva->type == SOURCE_ATOM_FORITER) {
			
			// special case for 'for' loops
			gen_print_foriter(atom,sva,out,atoms,NULL);
			break;
		}
		if (sva->type == SOURCE_ATOM_IMPORT_FROM) {
			// special case for from imports, it has no meaning in the source
			break;
		}

		if (sva->type == SOURCE_ATOM_IMPORT_NAME || sva->type == SOURCE_ATOM_FUNCTION
			|| sva->type == SOURCE_ATOM_CLASS) {
			if (sva->type == SOURCE_ATOM_FUNCTION) {
				source_atom_function * str = (source_atom_function*)sva->data;
				if (!(str->flags & SOURCE_FUNCTION_FLAG_LAMBDA)) {
					
					out->skip_line();
					gen_print_atom(sva, out, atoms);
					break;
				}
			}
			else {
				if (sva->type == SOURCE_ATOM_CLASS) {
					out->skip_line();
				}
				// special case for implicit name, we omit the store var here
				gen_print_atom(sva, out, atoms);
				break;
			}
		}

		else if (sva->type == SOURCE_ATOM_CALLFUNCTION) {			
			source_atom_callfunction * sf = (source_atom_callfunction*)sva->data;
			if (sf->flags & SOURCE_FUNCTION_FLAG_SPECIAL_CLASS) {				
				gen_print_atom(sf->vargs[0], out, atoms);				
				break;
			}
		}
		else if (sva->type == SOURCE_ATOM_UNPACK_SEQUENCE) {
			
			source_atom_unpacked_sequence * us = (source_atom_unpacked_sequence *)sva->data;
			if (us->rt->type == SOURCE_ATOM_FORITER) {
				gen_print_atom(sva, out, atoms);
				break;
			}
			int size = us->size;
			if (us->used < us->size - 1) {
				out->keepline = 1;
				out->bprintf("%s, ", sv->var);
			}
			else {
				out->keepline = 0;
				out->bprintf("%s = ", sv->var);
				gen_print_atom(sva, out, atoms);
			}
			us->used++;
			break;
		}


		if (!strcmp("__module__", sv->var)) {
			break;
		}
		

		out->bprintf("%s = ", sv->var);
		pylog("print regular store %i",sva->type);
		gen_print_atom(sva, out, atoms);
		break;

	}
	case SOURCE_ATOM_CONDITIONAL_LOOP: {
		out->insert_line_break();
		cond_chain * ch = (cond_chain*)atom->data;
		
		if (ch == NULL) {
			out->bprintf("while 1:");
			break;
		}

		source_atom * at = ch->atom_top;		
		
		if (at->type != SOURCE_ATOM_CONDJUMP) {		

			pylog("loop st atom %i", ch->atom_top->type);
			py_assert(at->type != 0, "Invalid atom on loop start");
			gen_print_atom(at, out, atoms);
			break;
		}		

		out->bprintf("while ");
		
		print_atom_chain(ch, out, atoms, 1);
		

		out->bprintf(":");

		break;
	}
	case SOURCE_ATOM_SLICE_W: {
		source_atoms_slice * slice = (source_atoms_slice*)atom->data;
		gen_print_atom(slice->origin, out, atoms);
		out->bprintf("[");
		int i;
		for (i = 0; i < slice->size; i++) {
			if (slice->params[i]) {
				gen_print_atom(slice->params[i], out, atoms);
			}
			if (i != slice->size - 1) {
				out->bprintf(":");
			}
		}
		out->bprintf("]");
		break;

	}
	case SOURCE_ATOM_SLICE: {
		source_atoms_slice * slice = (source_atoms_slice*)atom->data;
		int i;
		for (i = 0; i < slice->size; i++) {
			if (slice->params[i]->type != SOURCE_ATOM_NONE) {
				gen_print_atom(slice->params[i], out, atoms);
			}
			if (i != slice->size - 1) {
				out->bprintf(":");
			}
		}

		break;
	}
	case SOURCE_ATOM_CONDITIONAL: {
		cond_chain * ch = (cond_chain*)atom->data;
		
		source_atom * at = atoms->from_instruction(ch->node->final_inst);
		
		if (at->type == SOURCE_ATOM_FORITER) {
			
			if (ch->lambda != NULL) {
				gen_print_lambda(ch->lambda, out, atoms);
			}
			else {
				
			}
			break;
			
		}
		if (at->type == SOURCE_ATOM_CONDJUMP) {
			source_atom * a1 = (source_atom*)at->data;
			
			if (a1->type == SOURCE_ATOM_COMPARE) {
				source_atom_compare * cmp = (source_atom_compare*)a1->data;
				if (cmp->op == PyCmp_EXC_MATCH) {
					pylog("except type %i %i", ch->node->final_inst->off,cmp->params[1]->type);
					gen_print_atom(cmp->params[1], out, atoms);
					
					py_instruction * inst = ch->node->final_inst + 1;
					py_assert(inst->opcode == POP_TOP, "Unknown except construct");
					inst++;
					source_atom * a2 = atoms->from_instruction(inst);
					if (a2->type == SOURCE_ATOM_STORE_VAR) {
						
						source_atom_store_val * v = (source_atom_store_val*)a2->data;
						out->add_space_if_none();
						out->bprintf("as %s", v->var);
						a2->type = SOURCE_ATOM_DUMMY;
					}
					out->bprintf(":");
					break;
				}
			}
		}
		
		if (!(ch->flags & CHAIN_FLAG_INLINE)) {
			out->insert_line_break();
		}
		else {
			out->add_space_if_none();
			py_assert(ch->inline_atoms[0] != NULL, "Invalid atoms on inline conditional");
			gen_print_atom(ch->inline_atoms[0], out, atoms);
			out->add_space_if_none();
		}
		out->bprintf("if ");		
		int rt = print_atom_chain(ch, out,atoms,1);
		if (!(ch->flags & CHAIN_FLAG_INLINE) && !(ch->flags & CHAIN_FLAG_NODECORATION)) {
			out->bprintf(":");
		}
		else if (ch->flags & CHAIN_FLAG_INLINE) {
			if (ch->inline_atoms[1]) {
				out->bprintf("else: ");
				gen_print_atom(ch->inline_atoms[1], out, atoms);
			}
		}

		
		break;
	}
	case SOURCE_ATOM_STR: {
		source_atom_str * st = (source_atom_str*)atom->data;	
		
		gen_print_str_data(st, out);
		break;		
	}
	case SOURCE_ATOM_SETUP_WITH: {
		break;
	}
	case SOURCE_ATOM_COMPARE: {
		
		int i;
		source_atom_compare * cmp = (source_atom_compare*)atom->data;
			
		source_atom * ax = cmp->params[0];
		
		gen_print_atom(ax, out, atoms);
		
		out->bprintf(" %s ", gen_opcode_str[cmp->op]);

		ax = cmp->params[1];
		
		gen_print_atom(ax, out, atoms);
		break;
	}
	case SOURCE_ATOM_UNARYOPS: {
		source_atoms_ops * ops = (source_atoms_ops *)atom->data;

		switch (ops->op) {
		case UNARY_NOT:
			out->bprintf("not ");
			break;
		case UNARY_NEGATIVE:
			out->bprintf("-");
			break;
		case UNARY_POSITIVE:
			out->bprintf("+");
			break;
			
		}
		
		if (ops->flags & SOURCE_ATOM_OPS_OPONLY) {
			break;
		}
		gen_print_atom(ops->param1, out, atoms);
		break;
	}
	case SOURCE_ATOM_POP: {
		
		source_atom * at = (source_atom*)atom->data;
		if (at) {
			if (at->type == SOURCE_ATOM_SETUP_WITH) {
				break;
			}	
			if (at->type == SOURCE_ATOM_FORITER) {
				break;
			}
			gen_print_atom(at, out, atoms);
		}
		break;
	}
	case SOURCE_ATOM_LOAD_ATTR: {	
		source_atom_loadattr * la = (source_atom_loadattr*)atom->data;
		
		gen_print_atom(la->ref_atom, out, atoms);
		out->bprintf(".");
		out->bprintf( "%s", la->attr.bytes);
		break;
	}
	case SOURCE_ATOM_INT: {
		source_atom_int * ai = (source_atom_int*)atom->data;
		out->bprintf("%lli", ai->val);
		break;
	}
	case SOURCE_ATOM_CALLFUNCTION: {
		source_atom_callfunction * f = (source_atom_callfunction*)atom->data;

		if (f->flags & SOURCE_FUNCTION_FLAG_NESTED_DECORATOR) {
			//TODO replace this with a chain of call functions
			py_assert(f->vargs[f->varg_count - 1]->type == SOURCE_ATOM_FUNCTION,"Invalid nested decorators? %i", f->vargs[f->varg_count - 1]->type);
			source_atom_function *fx = (source_atom_function*)f->vargs[f->varg_count - 1]->data;
			out->bprintf("@%s", fx->annotation);
			int d = out->cur_depth;
			out->flush();
			out->set_depth(d);

			out->bprintf("@");
			gen_print_atom(f->fn, out, atoms);
			d = out->cur_depth;
			out->flush();
			out->set_depth(d);
			fx->annotation[0] = 0;
			gen_print_atom(f->vargs[f->varg_count - 1], out, atoms);
			break;
		}
		
		if (f->fn->type == SOURCE_ATOM_FUNCTION) {
			source_atom_function * ffx = (source_atom_function*)f->fn->data;
			if (ffx->flags & SOURCE_FUNCTION_FLAG_SETCOMP || ffx->flags & SOURCE_FUNCTION_FLAG_DICTCOMP) {
				source_atom_tree * fatoms = (source_atom_tree*)ffx->func->atoms;
				
				source_atom * fset = fatoms->root_head->atom;
				pylog("%i", fset->type);
				py_assert(fset->type == SOURCE_ATOM_BUILDSET, "Unknown <setcomp> construct");				

				source_atom_tree_node * nn = fatoms->root_head->next;
				source_atom * eval = nn->atom;
				
				pylog("call setcomp %i", eval->type);	
				if (eval->type == SOURCE_ATOM_JUMP) {
					nn = nn->next;
					eval = nn->atom;
				}
				
				fatoms->caller = f;
				fatoms->caller_atoms = atoms;
				
				if (eval->type == SOURCE_ATOM_RETURN) {
					gen_print_atom((source_atom*)eval->data, out, fatoms);
				}
				else {
					gen_print_atom(eval, out, fatoms);
				}

				fatoms->caller = NULL;
				atoms->caller_atoms = NULL;
				
				
				break;
				
			}
			else if (ffx->flags & SOURCE_FUNCTION_FLAG_GENERATOR) {

				source_atom_tree * fatoms = (source_atom_tree*)ffx->func->atoms;
				py_assert(fatoms != NULL, "Bad atoms on function");
				pylog("generator at %s", ffx->func->name);
				py_assert(f->varg_count > 0, "Unknown generator construct");
				source_atom * ffn = f->vargs[0];

				py_assert(ffn->type == SOURCE_ATOM_GETITER, "Unknown generator construct");
				ffn = (source_atom*)ffn->data;
				
				source_atom_tree_node * n = fatoms->root_head;
				
				if (n->atom->type == SOURCE_ATOM_STORE_VAR) {
					//py_assert(n->atom->type == SOURCE_ATOM_STORE_VAR, "Unknown generator construct (%i)", n->atom->type);

					source_atom_store_val * sv = (source_atom_store_val*)n->atom->data;

					out->bprintf("(");
					gen_print_atom(n->atom, out, fatoms);
					out->add_space_if_none();
					out->bprintf("in ");
					gen_print_atom(ffn, out, fatoms);
					out->bprintf(")");
				}
				else if (n->atom->type == SOURCE_ATOM_CONDITIONAL) {
					gen_print_atom(n->atom, out, fatoms);
				}
				else {					
					py_assert(0, "Unknown generator construct (%i)", n->atom->type);
				}
				
				break;

			}
		}
		
		
		gen_print_atom(f->fn, out, atoms);
		
		out->bprintf("(");
		
		int i;
		int p = 0;
		for (i = f->varg_count-1; i >=0; i--) {
			p = 1;
			if (i != f->varg_count - 1) {
				out->add_space_if_none();
			}
			
			gen_print_atom(f->vargs[i], out, atoms);
			if (i > 0) {
				out->bprintf(",");
			}
		}
		if (f->kwarg_count && p) {
			out->bprintf(",");
		}
		
		
		for (i = 0; i < f->kwarg_count; i++) {
			gen_print_atom(f->kwargs[i*2], out, atoms);
			out->bprintf("=");
			gen_print_atom(f->kwargs[i * 2+1], out, atoms);
			if (i != f->kwarg_count - 1) {
				out->bprintf(",");
			}
			
		}

		if (f->va) {	
			if (out->last() != '(') {
				out->bprintf(",");
			}
			out->bprintf("*");
			gen_print_atom(f->va, out, atoms);
		}

		if (f->kw) {
			if (out->last() != '(') {
				out->bprintf(",");
			}
			out->bprintf("**");
			gen_print_atom(f->kw, out, atoms);
		}
		
		
		out->bprintf(")");
		
		break;
	}
	case SOURCE_ATOM_IMPORT_FROM: {
		//nothing to print
		break;
	}
	case SOURCE_ATOM_IMPORT_NAME: {
		source_import_name * id = (source_import_name*)atom->data;
		if (id->fromlist->type == SOURCE_ATOM_NONE) {
			out->bprintf("import %s", id->symbol);
			
		}
		else {
			out->bprintf("from %s import ", id->symbol);
			
			gen_print_atom(id->fromlist, out, atoms);
		}
		break;
	}
	case SOURCE_ATOM_LOOP_START: {
		
		gen_print_atom((source_atom*)atom->data, out, atoms);
		break;
	}
	case SOURCE_ATOM_JUMP: {
		if (!atom->data && atom->inst->opcode == JUMP_ABSOLUTE) {
			if (atom->inst->to_jmp < atom->inst->off) {
				//out->bprintf("continue");
			}
		}
		break;
	}	
	case SOURCE_ATOM_WITH_BLOCK_GROUP: {
		earray * l = (earray*)atom->data;
		int i;
		out->backindent();
		out->bprintf("with ");
		for (i = 0; i < l->size; i++) {
			source_atom * at = earray_get(l, i, source_atom*);
			source_atom_with * ww = (source_atom_with*)at->data;
			out->add_space_if_none();
			py_assert(at->type == SOURCE_ATOM_WITH_BLOCK,"Invalid atom on with group");
			gen_print_atom(ww->expr, out, atoms);
			py_assert(ww->origin->type == SOURCE_ATOM_STORE_VAR || ww->origin->type == SOURCE_ATOM_POP,
				"Invalid atom on WITH origin (%i)", ww->origin->type);

			if (ww->origin->type == SOURCE_ATOM_STORE_VAR) {

				out->add_space_if_none();
				out->bprintf("as ");
				source_atom_store_val * sv = (source_atom_store_val*)ww->origin->data;
				out->bprintf("%s", sv->var);
			}
			if (i == l->size - 1) {
				out->bprintf(":");
			}
			else {
				out->bprintf(",");
			}

		}
		

		break;
	}
	case SOURCE_ATOM_DUMMY: {
		break;
	}
	case SOURCE_ATOM_RAISE: {
		source_atom_raise *r = (source_atom_raise*)atom->data;
		
		out->bprintf("raise ");
		int i;
		for (i = 0; i < r->size; i++) {
			gen_print_atom(r->params[i], out, atoms);
			if (i != r->size - 1) {
				out->bprintf(",");
			}
		}
		break;
	}
	case SOURCE_ATOM_STORE_SUBSCR: {
		source_atom_store_subscr_val * subs = (source_atom_store_subscr_val*)atom->data;
		gen_print_atom(subs->var, out, atoms);
		out->bprintf("[");
		gen_print_atom(subs->subscr,out,atoms);
		out->bprintf("] = " );
		gen_print_atom(subs->st_atom, out, atoms);
		break;
	}
	case SOURCE_ATOM_NONE: {
		if (out->empty) {
			break;
		}
		out->bprintf("None");
		break;
	}
	case SOURCE_ATOM_STORE_ATTR: {
		source_atom_store_attr * st = (source_atom_store_attr*)atom->data;
		
		gen_print_atom(st->obj, out, atoms);
		out->bprintf(".%s = ",st->var);
		gen_print_atom(st->st_atom, out, atoms);
		out->flush();
		
		break;
	}
	case SOURCE_ATOM_RETURN: {	
		
		out->bprintf("return ");
		gen_print_atom((source_atom*)atom->data, out, atoms);
		break;
	}
	case SOURCE_ATOM_SETUP_FINALLY: {
		break;
	}
	case SOURCE_ATOM_SETUP_EXCEPT: {
		break;
	}
	case SOURCE_ATOM_DUP: {
		py_assert(atom->data != NULL, "Unknown type from DUP");
		source_atom * at = (source_atom*)atom->data;
		if (at == atoms->get_except_placeholder()) {
			break;
		}
		gen_print_atom(at, out, atoms);
		break;
	}
	case SOURCE_ATOM_EXCEPT_PLACEHOLDER: {
		//out->bprintf("__Exception_placeholder");
		break;
	}
	case SOURCE_ATOM_TUPLECONST: {
		
		source_atom_tupleconst * c = (source_atom_tupleconst*)atom->data;
		if (!(c->flags & ATOM_TUPLE_FLAG_NO_PARENTHESIS)) {
			out->bprintf("(");
		}
		int i;
		char tmp[4096];
		for (i = 0; i < c->tuple->size; i++) {
		//	out->add_space_if_none();
			
			switch (((un_type*)c->tuple->data[i])->type) {
			case TYPE_STRING:
			case TYPE_STRINGREF: {
				source_atom_str str;
				str.bytes = un_resolve_str(c->tuple->data[i]);
				str.type = TYPE_STRING;
				str.subtype = SOURCE_STR_CONST;
				str.size = strlen(str.bytes);
				gen_print_str_data(&str, out);
				break;
			}
			default: {				
				un_to_printable(tmp, c->tuple->data[i]);
				out->bprintf("%s", tmp);
			}

			}
			
			if (i < c->tuple->size - 1 || (i==0 && c->tuple->size == 1)) {				
				out->bprintf(",", tmp);
			}

			
		}
	//	out->add_space_if_none();
		if (!(c->flags & ATOM_TUPLE_FLAG_NO_PARENTHESIS)) {
			out->bprintf(")");
		}
		
		break;
	}
	case SOURCE_ATOM_COMPLEX: {
		un_complex * c = un_coerce_complex(atom->data);
		out->bprintf("%.17lf+%.17lfj",c->real,c->imaginary);
		break;
	}
	case SOURCE_ATOM_FLOAT: {
		un_double * d = (un_double*)atom->data;
		out->bprintf("%.17lf", d->val);
		break;
	}
	case SOURCE_ATOM_BUILDSET: {
		out->bprintf("{");
		int i;
		source_atom_buildset * bs = (source_atom_buildset*)atom->data;
		for (i = 0; i < bs->size; i++) {
			source_atom * key = earray_get(&bs->data, i * 2, source_atom *);
			source_atom * value = earray_get(&bs->data, i * 2+1, source_atom *);
			gen_print_atom(key, out, atoms);
			out->bprintf(":");
			gen_print_atom(value, out, atoms);
			if (i < bs->size - 1) {
				out->bprintf(",");
			}
		}
		out->bprintf("}");
		break;
	}
	case SOURCE_ATOM_UNPACK_SEQUENCE: {
		
		source_atom_unpacked_sequence * us = (source_atom_unpacked_sequence *)atom->data;

		if (us->rt->type == SOURCE_ATOM_UNPACK_SEQUENCE) {
			//source_atom_str
			py_assert(0, "Unimplemented nested unpack");
		}

		

		/*py_assert(us->rt->type == SOURCE_ATOM_TUPLE || us->rt->type == SOURCE_ATOM_TUPLECONST
			|| us->rt->type == SOURCE_ATOM_CALLFUNCTION || us->rt->type == SOURCE_ATOM_STR ||
			us->rt->type == SOURCE_ATOM_FORITER || us->rt->type == SOURCE_ATOM_DUP,
			"Unknown UNPACK_SEQUENCE (%i)",us->rt->type);*/
		int i;

		if (us->rt->type == SOURCE_ATOM_DUP) {
			out->keepline = 1;
			
			break;
		}
		
		if (us->rt->type  == SOURCE_ATOM_FORITER) {
			
			char tmp[4096];
			char * t = tmp;
			for (i = 0; i < atom->referenced_nodes.size; i++) {
				source_atom_tree_node * n = earray_get(&atom->referenced_nodes, i, source_atom_tree_node*);
				source_atom * at = n->parent->atom;
				py_assert(at->type == SOURCE_ATOM_STORE_VAR,"Unknown FORITER UNPACK_SEQUENCE construct (%i)",at->type);
				source_atom_store_val * s = (source_atom_store_val*)at->data;
				
				sprintf(t, "%s", s->var);
				t += strlen(t);
				if (i < atom->referenced_nodes.size - 1) {
					sprintf(t, ",");
					t += strlen(t);
				}

			}

			gen_print_foriter(atom, us->rt, out, atoms,tmp);
		}
		else if (us->rt->type == SOURCE_ATOM_TUPLE) {
			source_atom_list * l = (source_atom_list*)us->rt->data;
			
			py_assert(l->size == us->size, "Unknown UNPACK_SEQUENCE");
			for (i = 0; i < l->size; i++) {
				source_atom * at = l->elems[i];
				gen_print_atom(at, out, atoms);
				if (i < (l->size - 1)) {
					out->bprintf(",");
				}
			}			
			
		}
		else if (us->rt->type == SOURCE_ATOM_STR) {
			source_atom_str * str = (source_atom_str*)us->rt->data;
			
			gen_print_atom(us->rt, out, atoms);
		}		
		else if (us->rt->type == SOURCE_ATOM_TUPLECONST) {
			source_atom_tupleconst * l = (source_atom_tupleconst*)us->rt->data;
			un_tuple * t = un_coerce_tuple(l->tuple);
			char tmp[4096];
			for (i = 0; i < t->size; i++) {
				un_to_printable(tmp, t->data[i]);
				out->bprintf("%s", tmp);
				if (i < (t->size - 1)) {
					out->bprintf(",");
				}
			}
		}
		else if (us->rt->type == SOURCE_ATOM_CALLFUNCTION) {
			gen_print_atom(us->rt, out, atoms);
		}
		else if (us->rt->type == SOURCE_ATOM_LOAD_ATTR) {
			gen_print_atom(us->rt, out, atoms);
		}
		else if (us->rt->type == SOURCE_ATOM_BINARYOPS) {
			source_binary_op * b = (source_binary_op*)us->rt->data;
			py_assert(b->type == BINARY_SUBSCR, "Unknown UNPACK_SEQUENCE form (%i) (%i)", us->rt->type, b->type);
			gen_print_atom(us->rt, out, atoms);
		}
		else {
			py_assert(0, "Unknown UNPACK_SEQUENCE form (%i)",us->rt->type);
		}
		
		break;
	}
	case SOURCE_ATOM_BREAK_LOOP: {
		out->bprintf("break");
		break;
	}
	case SOURCE_ATOM_TUPLE: {
		source_atom_list * l = (source_atom_list*)atom->data;
		if (!(l->flags & ATOM_TUPLE_FLAG_NO_PARENTHESIS)) {
			out->bprintf("(");
		}
		int i;
		for (i = 0; i < l->size; i++) {
			gen_print_atom(l->elems[i], out, atoms);
			if (i < (l->size - 1) || (i==0 && l->size == 1)) {
				out->bprintf(",");
			}
		}
		//out->add_space_if_none();
		if (!(l->flags & ATOM_TUPLE_FLAG_NO_PARENTHESIS)) {
			out->bprintf(")");
		}
		break;

	}
	case SOURCE_ATOM_SIMPLE_CHAIN: {
		
		source_atom * cond = (source_atom*)atom->data;
		cond_chain * cc = (cond_chain*)cond->data;

		if (cc->extra_data) {	
			if (cc->extra_data->type == SOURCE_ATOM_CONDITIONAL) {
				cond_chain * ch = (cond_chain*)cc->extra_data->data;
				ch->flags |= CHAIN_FLAG_NODECORATION;
				
				gen_print_atom(cc->extra_data, out, atoms);
				out->add_space_if_none();
				out->bprintf("or ");
				//FIXME maybe add () around every condition here;
				flip_chain(cc);		
				print_atom_chain(cc, out, atoms, 1);
				out->bprintf(":");
				break;
				
			}
			else if (cc->extra_data->type == SOURCE_ATOM_CALLFUNCTION) {
				source_atom_callfunction * cf = (source_atom_callfunction*)cc->extra_data->data;
				/*int d = out->cur_depth;
				out->flush();
				out->set_depth(d - 1);*/
				gen_print_atom(cf->fn, out, atoms);
				out->bprintf("(");
				if (cf->varg_count > 0) {
					if (cf->vargs[0]->type == SOURCE_ATOM_UNARYOPS) {
						source_atoms_ops * bops = (source_atoms_ops*)cf->vargs[0]->data;
						bops->flags |= SOURCE_ATOM_OPS_OPONLY;
						gen_print_atom(cf->vargs[0], out, atoms);
						out->bprintf("(");
						// find unary referenced inst/atom inside the same node
						if (cf->vargs[0]->inst->stackbacks_sz > 0) {
							int i;
							for (i = 0; i < cf->vargs[0]->inst->stackbacks_sz; i++) {
								py_instruction * pinst = cf->vargs[0]->inst->stackbacks[i].stack_referrals[0];
							//	atom->inst->

							//	if (pinst->off > )
							}
						}
						else {
							gen_print_atom(cf->vargs[0], out, atoms);
						}
						out->bprintf("and ");
						print_atom_chain(cc, out, atoms, 1);
						out->bprintf(")");						
					}
					else if (cf->vargs[0]->type == SOURCE_ATOM_COMPARE) {
						print_atom_chain(cc, out, atoms, 1);
						out->bprintf(")");
					}
					else {
						
						out->bprintf("muh args ");
						out->bprintf("and ");
					}
					break;
				}
				print_atom_chain(cc, out, atoms, 1);
				out->bprintf(")");
				break;
			}
			else {
				gen_print_atom(cc->extra_data, out, atoms);
				out->bprintf(" and ");
			}
		}
		print_atom_chain(cc,out,atoms,1);
		
		break;
	}
	case SOURCE_ATOM_DELETE_SLICE: {
		source_atoms_delete_slice * sd = (source_atoms_delete_slice*)atom->data;
		out->bprintf("del ");
		gen_print_atom(sd->st, out, atoms);
		out->bprintf("[");
		switch (sd->type) {
		case DELETE_SLICE: {
			out->bprintf(":");
			break;
		}
		case DELETE_SLICE_1: {
			gen_print_atom(sd->params[0], out, atoms);
			out->bprintf(":");
			break;
		}
		case DELETE_SLICE_2: {			
			out->bprintf(":");
			gen_print_atom(sd->params[0], out, atoms);
			break;
		}
		case DELETE_SLICE_3: {
			gen_print_atom(sd->params[0], out, atoms);
			out->bprintf(":");
			gen_print_atom(sd->params[1], out, atoms);
			break;
		}
		case DELETE_SUBSCR: {
			gen_print_atom(sd->params[0], out, atoms);
			break;
		}
		}
		out->bprintf("]");
		break;
	}
	case SOURCE_ATOM_STORE_SLICE: {
		source_atoms_store_slice * sl = (source_atoms_store_slice*)atom->data;

		gen_print_atom(sl->st, out, atoms);
		out->bprintf("[");
		
		switch (sl->type) {
		case STORE_SLICE: {
			out->bprintf(":]");			
			break;
		}
		case STORE_SLICE_1: {
			gen_print_atom(sl->params[0], out, atoms);
			out->bprintf(":]");			
			break;
		}
		case STORE_SLICE_2: {
			out->bprintf(":");
			gen_print_atom(sl->params[0], out, atoms);
			out->bprintf("]");			
			break;
		}
		case STORE_SLICE_3: {
			gen_print_atom(sl->params[0], out, atoms);
			out->bprintf(":");
			gen_print_atom(sl->params[1], out, atoms);
			out->bprintf("]");			
			break;
		}
		}
		if (!(sl->flags&SLICE_FLAG_NO_RIGHTHAND)) {
			out->bprintf(" = ");
			gen_print_atom(sl->dest, out, atoms);
		}
		break;
	}
	case SOURCE_ATOM_CONTINUE: {
		out->bprintf("continue");
		break;
	}
	case SOURCE_ATOM_LIST: {
		
		source_atom_list * l = (source_atom_list*)atom->data;
		out->bprintf("[");
		int i;
		for (i = 0; i < l->size; i++) {
			gen_print_atom(l->elems[i], out, atoms);
			if (i < (l->size - 1)) {
				out->bprintf(",");
			}
		}
		out->bprintf("]");
		break;
		
	}
	case SOURCE_ATOM_DELEGATE: {
		source_atom * del = (source_atom*)atom->data;
		gen_print_atom(del, out, atoms);
		break;
	}
	case SOURCE_ATOM_YIELD: {
		out->bprintf("yield ");

		gen_print_atom((source_atom*)atom->data, out, atoms);
		break;
	}
	case SOURCE_ATOM_CLASS: {
		source_atom_class * cl = (source_atom_class*)atom->data;
		int i;
		out->bprintf("class %s(", un_resolve_str(cl->cls->class_name));
		/*for (i = 0; i < cl->cls->base_names->size; i++) {
			char * name = un_resolve_str(cl->cls->base_names->data[i]);
			if (i == cl->cls->base_names->size - 1) {
				out->bprintf("%s", name);
			}
			else {
				out->bprintf("%s,", name);
			}
		}*/
		
		if (cl->baseclnames->type == SOURCE_ATOM_TUPLE) {
			source_atom_list * l = (source_atom_list*)cl->baseclnames->data;
			l->flags |= ATOM_TUPLE_FLAG_NO_PARENTHESIS;
		}
		else if (cl->baseclnames->type == SOURCE_ATOM_TUPLECONST) {
			source_atom_tupleconst * t = (source_atom_tupleconst*)cl->baseclnames->data;
			t->flags |= ATOM_TUPLE_FLAG_NO_PARENTHESIS;
		}
		gen_print_atom(cl->baseclnames, out, atoms);
		out->bprintf("):");
		int ndepth = out->cur_depth;
		out->flush();
		source_atom_function * f = (source_atom_function*)cl->basefn->data;
		
		gen_print_source(f->func, out,ndepth+1);
		break;
	}
	case 0: {
		out->bprintf("zero atom %s", atom->inst->highlevel_name);
		break;
	}
	default:
		py_assert(0, "Unimplemented atom print type %i", atom->type);
	}
}

void gen_print_pass(int depth, source_gen_out_buf * fout) {
	pylog("print pass");
	fout->set_depth(depth);
	fout->bprintf("pass");
	fout->flush();
}

void gen_print_source(py_function * fn, source_gen_out_buf * fout, int base_depth) {
	py_assert(fn->atoms != NULL, "Invalid atoms in function");
	source_atom_tree * atoms = (source_atom_tree*)fn->atoms;
	int i;

	int special_block = 0;
	int block_has_data = 0;
	int group_has_data = 0;
	int block_depth = 0;
	pylog("Starting source printing for %s", fn->name);
	source_atom_tree_node * an = atoms->root_head;
	
	while (an) {
		
		if (an->atom->flags & ATOM_FLAG_BREAK_LINE) {
			fout->empty = 0;
			fout->flush();
		}
		if (an->atom->flags & ATOM_FLAG_TRY_BLOCK) {
			py_assert(an->atom->depth > 0, "Bad depth on try block %i", an->atom->depth);
			fout->set_depth(an->atom->depth - 1 + base_depth);
			fout->bprintf("try:");
			fout->flush();
		}
		if (an->atom->flags & ATOM_FLAG_EXCEPT_BLOCK) {
			pylog("print an except atom");
			
			py_assert(an->atom->depth > 0, "Bad depth on else block %i", an->atom->depth);
			fout->set_depth(an->atom->depth - 1 + base_depth);
			
			if (an->atom->type == SOURCE_ATOM_POP) {
				fout->bprintf("except:");
				fout->flush();
				special_block = ATOM_FLAG_EXCEPT_BLOCK;
				block_has_data = 0;
				block_depth = an->atom->depth;
				an = an->next;
				continue;
			}
			pylog("atom %i", an->atom->type);
			//py_assert(an->atom->type == SOURCE_ATOM_CONDITIONAL, "Unknown except block %i",an->atom->type);
			if (an->atom->type != SOURCE_ATOM_DUMMY) {
				fout->bprintf("except ");

				gen_print_atom(an->atom, fout, atoms);
				fout->flush();
				special_block = ATOM_FLAG_EXCEPT_BLOCK;
				block_has_data = 0;
				block_depth = an->atom->depth;
			}
			
			an = an->next;
			continue;
		}
		if (an->atom->flags & ATOM_FLAG_FINALLY_BLOCK) {
			py_assert(an->atom->depth > 0, "Bad depth on else block %i", an->atom->depth);
			fout->set_depth(an->atom->depth - 1 + base_depth);
			fout->bprintf("finally:");
			fout->flush();
		}
		if (an->atom->flags & ATOM_FLAG_COND_ELSE) {
			if (special_block == ATOM_FLAG_EXCEPT_BLOCK) {				
				if (!block_has_data) {					
					gen_print_pass(an->atom->depth - 1+ base_depth, fout);
				}
				special_block = 0;
				an = an->next;
				continue;
			}
			pylog("atom %i\n", an->atom->type);
			py_assert(an->atom->depth > 0, "Bad depth on else block %i",an->atom->depth);
			fout->set_depth(an->atom->depth-1 + base_depth);
			fout->bprintf("else:");
			fout->flush();
		}

		if (!an->next && an->atom->type == SOURCE_ATOM_RETURN) {
			source_atom * at = (source_atom*)an->atom->data;
			if (at->type == SOURCE_ATOM_NONE || at->type == SOURCE_ATOM_DUMMY)  {
				break;
			}
		}
		if (an->atom->type == SOURCE_ATOM_POP) {
			// check if type is printable in a single line
			source_atom * at = (source_atom*)an->atom->data;
			
			if (at->type == SOURCE_ATOM_STR) {
				an = an->next;
				continue;
			}
			if (at->type == SOURCE_ATOM_INT) {
				an = an->next;
				continue;
			}
			if (at->type == SOURCE_ATOM_COMPARE) {
				an = an->next;
				continue;
			}
			if (at->type == SOURCE_ATOM_DUP) {
				//FIXME drill deeper into dup
				an = an->next;
				continue;
			}

			
			
		}

		if (an->atom->type == SOURCE_ATOM_STR || an->atom->type == SOURCE_ATOM_LIST) {
			an = an->next;
			continue;
		}
		if (special_block == ATOM_FLAG_EXCEPT_BLOCK && !block_has_data && block_depth > an->atom->depth) {
			special_block = 0;
			gen_print_pass(base_depth + block_depth, fout);
		}
		//py_assert(an->atom->depth >= 0, "Invalid depth on atom %i", an->atom->type);
		if (!fout->keepline) {
			fout->set_depth(an->atom->depth + base_depth);
		}		

		pylog("gen atom %i %i %s %X, depth %i, %llX", an->atom->type, an->atom->inst ? an->atom->inst->off : -1,
			an->atom->inst ? an->atom->inst->highlevel_name : "abstract",an->atom->flags,an->atom->depth,an->atom);
		
		fout->keepline = 0;
		if (!(an->atom->flags & ATOM_FLAG_DELEGATE)) {
			gen_print_atom(an->atom, fout, atoms);
		}
		if (!fout->empty) {
			block_has_data = 1;
			group_has_data = 1;
		}
		if (!fout->keepline) {
			fout->flush();
		}		
		an = an->next;
		
	}
	if (!group_has_data && base_depth > 0) {
		
		if (!(fn->flags & PY_FUNCTION_FLAG_CLASSGEN)) {
			
			gen_print_pass(base_depth, fout);
		}
	}
	
}

/* debug functions */



void gen_print_atom_structure(py_function * fn, source_atom * atom) {
	py_instruction * inst = &fn->instruction_set[atom->idx];
	printf("dbg %s, len: %i\n", inst->highlevel_name,atom->len);
	if (inst->opcode == COMPARE_OP) {
		source_atom * a1 = ((source_atom**)atom->data)[0];
		source_atom * a2 = ((source_atom**)atom->data)[1];
		py_instruction * inst1 = &fn->instruction_set[a1->idx];
		py_instruction * inst2 = &fn->instruction_set[a2->idx];
		printf("op1 %s %i\n", inst1->highlevel_name, inst1->off);
		printf("op2 %s %i\n", inst2->highlevel_name, inst2->off);
	}
	else if (inst->opcode == CALL_FUNCTION) {
		source_atom_callfunction * c = (source_atom_callfunction*)atom->data;
		py_instruction * inst1 = &fn->instruction_set[((source_atom*)c->fn)->idx];
		printf("vargs: %i, kwargs: %i\n", c->varg_count, c->kwarg_count);
		
		printf("code obj: %s %i\n",inst1->highlevel_name,inst1->off);
		int i;
		for (i = 0; i < c->varg_count; i++) {
			source_atom * at = ((source_atom**)c->vargs)[i];
			inst1 = &fn->instruction_set[at->idx];
			printf("varg: %s %i\n", inst1->highlevel_name, inst1->off);
		}
		for (i = 0; i < c->kwarg_count; i++) {
			source_atom * at = ((source_atom**)c->kwargs)[i*2];
			inst1 = &fn->instruction_set[at->idx];
			printf("kwarg-key: %s %i\n", inst1->highlevel_name, inst1->off);
			at = ((source_atom**)c->kwargs)[i * 2+1];
			inst1 = &fn->instruction_set[at->idx];
			printf("kwarg: %s %i\n", inst1->highlevel_name, inst1->off);
		}
	}
}


#undef pylog
#define pylog(...)