#pragma once

#include "common.h"
#include "opcodes.h"

// Basic structure definitions (compatible with source-gen.cpp)
struct source_atom {
    int len;
    int type;
    void* data;
    py_instruction* inst;
    // Note: This is a minimal definition - the real structure has more fields
};

struct source_atom_tree {
    // Minimal definition - see source-gen.cpp for full structure
    void* dummy;
};

struct source_binary_op {
    int type;
    source_atom* op1;
    source_atom* op2;
    // Note: This is a minimal definition
};

struct source_atom_callfunction {
    source_atom* fn;
    int varg_count;
    int kwarg_count;
    source_atom* va;
    source_atom* kw;
    // Note: This is a minimal definition
};

struct source_atom_list {
    int size;
    source_atom** elems;
    // Note: This is a minimal definition
};

// Source atom types from source-gen.cpp enum SOURCE_TYPES
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
    SOURCE_ATOM_MAP_ADD
};

typedef struct opcode_info {
    int opcode;
    char name[64];
    int stack_effect;
    int has_arg;
    int category; // 0=unknown, 1=binary, 2=unary, 3=load, 4=store, 5=call, etc.
} opcode_info;

typedef struct python_source_context {
    char* python_root_path;
    opcode_info* opcodes;
    int opcode_count;
    char python_version[32];
} python_source_context;

typedef struct bytecode_atom_mapping {
    int start_offset;
    int end_offset;
    source_atom* atom;
    int overlaps_count;
    struct bytecode_atom_mapping** overlapping_atoms;
} bytecode_atom_mapping;

typedef struct atom_extraction_result {
    source_atom** atoms;
    int atom_count;
    bytecode_atom_mapping* mappings;
    int mapping_count;
} atom_extraction_result;

#ifdef __cplusplus
extern "C" {
#endif

python_source_context* init_python_source_context(const char* python_root_path);
atom_extraction_result* extract_atoms_from_bytecode(python_source_context* ctx,
                                                   py_instruction* bytecode_array,
                                                   int bytecode_count);
void gen_source_obj_dynamic(python_source_context* ctx, py_function* fn, int idx, 
                           source_atom_tree* atoms, source_atom* out);
void cleanup_extraction_result(atom_extraction_result* result);
void cleanup_python_source_context(python_source_context* ctx);

#ifdef __cplusplus
}
#endif