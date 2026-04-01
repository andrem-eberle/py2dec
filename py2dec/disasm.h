#pragma once

#include "common.h"
#include "unmarshal.h"
#include "earray.h"
#include "py_gen.h"


typedef struct py_disasm_context {
	py_disasm_context() {

	}

} py_disasm_context;

typedef struct py_disasm_output {
	py_disasm_output() {
		fns_sz = 0;
		classes_sz = 0;
	}
	py_function * fns;
	int fns_sz;

	py_function * closures;
	int closures_sz;

	py_class * classes;
	int classes_sz;
	py_instruction * instruction_set;
	int instruction_set_size;
} py_disasm_output;

un_tuple * disasm_build_unpacked_tuple(py_instruction * inst, py_function * base);
char * disasm_pretty_print(char * out, py_instruction * inst, int refline);
char * disasm_pretty_print_function(char * out, py_function * function);
void disasm_print_instructions(FILE * fp, py_instruction * instruction_set, int instruction_set_size);
int disasm_process(byte * data, int sz, py_function * pout);
void disasm_print_all(py_function * pout);
void set_up_instruction_tos(py_instruction * inst);
