#include "common.h"
#include "disasm.h"
#include "unmarshal.h"
#include "flow.h"
#include "hash.h"
#include "source-gen.h"
#include "source-gen.h"
#include "stack-solver.h"
#include "global_config.h"
#include "source-util.h"
#include "translate.h"

#ifdef _WIN32
#include <Windows.h>
#include <dbghelp.h>
#endif

#ifdef __linux__
#include <signal.h>
#endif

#ifdef _WIN32
static int handlingExcept = 0;
LONG WINAPI excep_handler(struct _EXCEPTION_POINTERS *ExceptionInfo) {

	UNREFERENCED_PARAMETER(ExceptionInfo);
	if (handlingExcept) {
		fflush(stdout);
		exit(0);
	}

	printf("Exception %X\n", ExceptionInfo->ExceptionRecord->ExceptionCode);
	void         * stack[100];
	
	handlingExcept = 1;
	
	USHORT frames = CaptureStackBackTrace((ULONG)0, (ULONG)100, stack, NULL);

	SYMBOL_INFO  * symbol;
	HANDLE         process;

	process = GetCurrentProcess();

	SymInitialize(process, NULL, TRUE);

	symbol = (SYMBOL_INFO *)calloc(sizeof(SYMBOL_INFO) + 256 * sizeof(char), 1);
	symbol->MaxNameLen = 255;
	symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
	printf("0x%X\n", ExceptionInfo->ContextRecord->Rip);
	int i;
	for (i = 0; i < frames; i++) {
		SymFromAddr(process, (DWORD64)(stack[i]), 0, symbol);
		printf("%i: %s - 0x%0X\n", frames - i - 1, symbol->Name, symbol->Address);
	}
	fflush(stdout);
	
	exit(0);
}
#endif

void print_usage() {
	printf("Usage: py2dec [OPTIONS] <file>\n");
	printf("<file> is a compiled python file (usually .pyc)\n");
	printf("\n");
	printf("Options:\n");
	printf("--output-asm <out_file_asm>\t\toutputs the disassembled bytecode to <out_file_asm>\n");
	printf("-o <out_file>\t\toutputs the decompiled code <out_file>. Defaults to stdout\n");
}

int parse_args(int argc, char * argv[]) {
	if (argc < 2) {
		print_usage();		
		return -1;
	}
	int i;
	for (i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			if (!strcmp(argv[i], "--output-asm")) {
				i++;
				if (i >= argc) {
					print_usage();
					return -1;
				}
				global_config.output_asm = 1;
				
				strcpy(global_config.output_asm_file, argv[i]);
			}
			else if (!strcmp(argv[i], "-o")) {
				i++;
				if (i >= argc) {
					print_usage();
					return -1;
				}
				
				strcpy(global_config.output_file, argv[i]);
				
				
			}
			else {
				print_usage();
				return -1;
			}
		}
		else {
			break;
		}
	}
	if (i >= argc) {
		printf("py2dec: missing file operand\n");
		return -1;
	}
	
	global_config.filename = argv[i];
	return 0;
}

#ifdef __linux__
void segfault_trap(int sig, siginfo_t *si, void *arg) {
	printf("segfault\n");
	exit(0);
}
#endif

void apply_flow_recursive(py_function * func, char * prefix) {
	flow_graph * graph = new flow_graph();
	func->flow_nodes = graph;
	build_flow(func->instruction_set, func->instruction_set_size, graph, prefix);

	char tmp[1024];
	int i,j;
	py_function * nested = func->nested_functions;
	for (i = 0; i < func->nested_functions_sz; i++) {
		sprintf(tmp, "%s.%s", prefix, nested->name);
		apply_flow_recursive(nested, tmp);
		nested = nested->next;
	}

	nested = func->nested_closures;
	while (nested) {
		sprintf(tmp, "%s.%s", prefix, nested->name);
		apply_flow_recursive(nested, tmp);
		nested = nested->next;
	}

	py_class * nclass = func->nested_classes;

	for (i = 0; i < func->nested_classes_sz; i++) {
		nested = nclass->methods;
		while (nested) {
			sprintf(tmp, "%s.%s.%s", prefix, nclass->class_name,nested->name);
			apply_flow_recursive(nested, tmp);
			nested = nested->next;
		}
		nclass = nclass->next;
	}
}

void apply_solver_recursive(py_function * func) {
	top_down_solver2(func);
	
	py_function * nested = func->nested_functions;
	int i;
	for (i = 0; i < func->nested_functions_sz; i++) {		
		apply_solver_recursive(nested);
		nested = nested->next;
	}

	nested = func->nested_closures;
	while (nested) {
		apply_solver_recursive(nested);
		nested = nested->next;
	}

	py_class * nclass = func->nested_classes;

	for (i = 0; i < func->nested_classes_sz; i++) {
		nested = nclass->methods;
		while (nested) {
			apply_solver_recursive(nested);
			nested = nested->next;
		}
		nclass = nclass->next;
	}
}

int main(int argc, char * argv[]) {

#ifdef _WIN32
	AddVectoredExceptionHandler(0, excep_handler);
#elif __linux__
	struct sigaction sa;

	memset(&sa, 0, sizeof(struct sigaction));
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = segfault_trap;
	sa.sa_flags   = SA_SIGINFO;

	sigaction(SIGSEGV, &sa, NULL);
#endif
	int rt;
	if (rt = parse_args(argc, argv)) {
		return rt;
	}
	
	hashmap * h = new hashmap(4);

	init_strings();
	init_opcode_map();
	init_unmarshal();
	init_gen_print();
	init_solver2();
	init_solver();

	printf("py2dec - decompiling %s\n", global_config.filename);
	FILE * fp = fopen(global_config.filename, "rb");
	if (!fp) {
		printf("ERROR - file not found: %s\n", global_config.filename);
		return -1;
	}
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	byte * ffile = (byte*)malloc(size);
	int sz = fread(ffile, 1, size, fp);
	fclose(fp);

	py_function pout;

	rt = disasm_process(ffile,sz,&pout);
	if (rt < 0) {
		return rt;
	}

	py_function ptranslate;
	py_function * target = &pout;
#ifdef USE_INTERMEDIATE_LANGUAGE
	translate(&pout, &ptranslate);
	target = &ptranslate;
#endif

	if (global_config.output_asm) {
		disasm_print_all(target);
	}
	
#ifdef USE_INTERMEDIATE_LANGUAGE
	
	
	printf("Building flow graph...\n");
	apply_flow_recursive(target, "main__");
	
	printf("Solving stack references...\n");
	apply_solver_recursive(target);
#endif
	

	source_gen_out_buf buf;
	if (global_config.output_file[0]) {

		buf.output = fopen(global_config.output_file, "wb");
		if (!buf.output) {
			fprintf(stderr, "ERROR - could not open output file: %s. \nAborting...\n", global_config.output_file);			
			return -1;
		}
		printf("Writing decompiled file to %s.\n", global_config.output_file);
	}
	else {
		buf.output = stdout;
		printf("Writing decompiled file to stdout\n");
	}
	
	printf("Generating source...\n");
	gen_source(target, &buf);

	printf("Done.\n");

	return 0;
	
}
