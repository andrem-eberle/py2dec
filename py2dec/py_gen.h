#pragma once
#include "common.h"
#include "earray.h"
#include "unmarshal.h"

#ifdef LOG_STACK_SOLVER
#define pylog(...) pylog_type("py-gen",__VA_ARGS__)
#endif

struct py_function;
struct py_instruction;

typedef struct py_stackback {
	struct py_instruction ** stack_referrals;
	
	py_stackback() {
		memset(this, 0, sizeof(py_stackback));
	}
} py_stackback;

typedef struct py_instruction {
	char highlevel_name[64];
	uint32 opcode;
	uint32 arg;
	int has_arg;
	int predef_arg;
	void * arg_ptr;
	int line_no;
	int idx;
	int off;
	int old_off;
	int to_jmp;
	int jmp_conditional;
	int eob;
	int brk;
	int loop_data;
	int stack_op;
	int tos_op_in;
	int tos_op_out;
	int tos_op_peek;

	py_instruction * translated;

	py_instruction ** stack_referrals;
	int stack_referrals_sz;

	earray reverse_stack_referrals;

	py_stackback * stackbacks;
	int stackbacks_sz;

	void * co_atom;

	int add_stackback() {
		if (!stackbacks) {
			stackbacks = new py_stackback[1];
			stackbacks_sz = 1;
			return stackbacks_sz-1;
		}
		py_stackback * old = stackbacks;
		stackbacks = new py_stackback[stackbacks_sz+1];
		memcpy(stackbacks, old, stackbacks_sz * sizeof(py_stackback));
		delete[] old;
		stackbacks_sz++;
		return stackbacks_sz - 1;
	}

	void coallesce() {
		
		if (!stackbacks_sz) {
			return;
		}
		memcpy(stack_referrals, stackbacks[0].stack_referrals, stack_referrals_sz * sizeof(py_instruction*));
		int i;
		int eq = 1;
		for (i = 0; i < stackbacks_sz; i++) {
			int j,k;
			
			for (j = 0; j < stack_referrals_sz; j++) {				
				py_instruction * inst = stackbacks[i].stack_referrals[j];
				
				for (k = i+1; k < stackbacks_sz; k++) {		
					if (inst != stackbacks[k].stack_referrals[j]) {
						eq = 0;
						break;
					}
				}
				if (!eq) {
					break;
				}
			}
			if (!eq) {
				break;
			}
		}
		
		if (eq) {	
			pylog("deletes");
			for (i = 0; i < stackbacks_sz; i++) {
				delete[] stackbacks[i].stack_referrals;
				
			}
			delete[] stackbacks;
			stackbacks_sz = 0;
		}
	}

	void expand_stackback(int n) {
		stackbacks = new py_stackback[n];
		stackbacks_sz = n;
		pylog("expand %i %i", n, stack_referrals_sz);
		int i;
		for (i = 0; i < n; i++) {
			stackbacks[i].stack_referrals = new py_instruction*[stack_referrals_sz];
			memcpy(stackbacks[i].stack_referrals, stack_referrals, stack_referrals_sz * sizeof(py_instruction*));
		}
	}

	py_instruction() {
		memset(this, 0, sizeof(py_instruction));
		to_jmp = -1;		
	}

	py_instruction(int iopcode) {
		opcode = iopcode;
		memset(this, 0, sizeof(py_instruction));
		to_jmp = -1;
	}

} py_instruction;

typedef struct py_class {
	py_instruction * inst;
	un_str * class_name;
	un_tuple * base_names;
	un_code * generator_function;
	py_function * methods;
	py_function * gen_function;
	int methods_sz;
	int idx;
	py_instruction * instruction_set;
	int instruction_set_size;
	py_class() {
		memset(this, 0, sizeof(py_class));
	}
	py_class * next;
} py_class;

typedef struct py_function_parameter {
	char * p_name;
	void * default_value;

	py_function_parameter() {
		p_name = NULL;
		default_value = NULL;
	}
	py_function_parameter(char * name) {
		p_name = name;
		default_value = NULL;
	}
} py_function_parameter;

struct flow_graph;

#define PY_FUNCTION_FLAG_CLASSGEN		1
#define PY_FUNCTION_FLAG_TRANSLATED		2

typedef struct py_function {
	py_instruction inst;

	int argcount;
	py_class * parent_class; // if any
	un_code * code;
	py_instruction * instruction_set;
	int instruction_set_size;
	int instruction_set_fullsize;

	uint32 flags;
	
	py_instruction ** instruction_by_offset;

	py_function * translated;
	char name[512];
	py_function_parameter* regular_parameters;
	char ** arg_names;
	char * var_arg;
	char * kw_arg;
	un_tuple * freevars;

	earray loop_block_data;

	earray try_block_data;

	py_function() {
		memset(this, 0, sizeof(py_function));
	}

	void set_params(int size) {
		argcount = size;
		regular_parameters = new py_function_parameter[size];
		arg_names = new char*[size];
	}

	int idx;
	py_function * nested_functions;
	int nested_functions_sz;
	py_function * nested_closures;
	int nested_closures_sz;

	py_class * nested_classes;
	int nested_classes_sz;

	py_function * next;
	flow_graph * flow_nodes;

	void * atoms;
	int atoms_sz;

	int match_name_args(py_function * f1) {
		if (strcmp(f1->name, name)) {
			return 0;
		}
	}

} py_function;

#undef pylog
#define pylog(...)