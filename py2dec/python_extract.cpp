#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "common.h"
#include "source-gen.h"
#include "python_extract.h"

#define MAX_OPCODE_NAME 64
#define MAX_OPCODES 512
#define MAX_LINE_LENGTH 1024

// Parse Python's opcode.h file to extract opcode definitions
int parse_opcode_definitions(python_source_context* ctx) {
    char opcode_path[512];
    snprintf(opcode_path, sizeof(opcode_path), "%s/Include/opcode.h", ctx->python_root_path);
    
    FILE* fp = fopen(opcode_path, "r");
    if (!fp) {
        // Try alternate location
        snprintf(opcode_path, sizeof(opcode_path), "%s/Include/cpython/opcode.h", ctx->python_root_path);
        fp = fopen(opcode_path, "r");
    }
    
    if (!fp) {
        printf("ERROR: Could not find opcode.h in Python source tree\n");
        return 0;
    }
    
    ctx->opcodes = (opcode_info*)malloc(sizeof(opcode_info) * MAX_OPCODES);
    ctx->opcode_count = 0;
    
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), fp)) {
        // Parse #define OPCODE_NAME   NUMBER
        if (strncmp(line, "#define ", 8) == 0) {
            char opname[MAX_OPCODE_NAME];
            int opcode;
            
            if (sscanf(line, "#define %s %d", opname, &opcode) == 2) {
                if (ctx->opcode_count < MAX_OPCODES) {
                    opcode_info* info = &ctx->opcodes[ctx->opcode_count++];
                    info->opcode = opcode;
                    strncpy(info->name, opname, MAX_OPCODE_NAME - 1);
                    info->name[MAX_OPCODE_NAME - 1] = '\0';
                    
                    // Categorize opcode by name pattern
                    if (strstr(opname, "BINARY_")) {
                        info->category = 1;
                    } else if (strstr(opname, "UNARY_")) {
                        info->category = 2;
                    } else if (strstr(opname, "LOAD_")) {
                        info->category = 3;
                    } else if (strstr(opname, "STORE_")) {
                        info->category = 4;
                    } else if (strstr(opname, "CALL_")) {
                        info->category = 5;
                    } else if (strstr(opname, "BUILD_")) {
                        info->category = 6;
                    } else {
                        info->category = 0;
                    }
                    
                    // Set has_arg based on HAVE_ARGUMENT threshold (usually 90)
                    info->has_arg = (opcode >= 90);
                }
            }
        }
    }
    
    fclose(fp);
    printf("Parsed %d opcodes from Python source\n", ctx->opcode_count);
    return 1;
}

// Parse compile.c to extract stack effects for each opcode
int parse_stack_effects(python_source_context* ctx) {
    char compile_path[512];
    snprintf(compile_path, sizeof(compile_path), "%s/Python/compile.c", ctx->python_root_path);
    
    FILE* fp = fopen(compile_path, "r");
    if (!fp) {
        printf("WARNING: Could not find compile.c, using heuristic stack effects\n");
        return 0;
    }
    
    char line[MAX_LINE_LENGTH];
    int in_stack_effect_function = 0;
    
    while (fgets(line, sizeof(line), fp)) {
        // Look for stack_effect function
        if (strstr(line, "stack_effect(") && strstr(line, "int")) {
            in_stack_effect_function = 1;
            continue;
        }
        
        if (in_stack_effect_function) {
            // Parse case statements like "case BINARY_ADD: return -1;"
            if (strstr(line, "case ")) {
                char opname[MAX_OPCODE_NAME];
                int effect = 0;
                
                if (sscanf(line, " case %[^:]: return %d;", opname, &effect) == 2) {
                    // Find this opcode in our list
                    for (int i = 0; i < ctx->opcode_count; i++) {
                        if (strcmp(ctx->opcodes[i].name, opname) == 0) {
                            ctx->opcodes[i].stack_effect = effect;
                            break;
                        }
                    }
                }
            }
            
            // End of function
            if (strstr(line, "}") && strchr(line, '}') == strrchr(line, '}')) {
                in_stack_effect_function = 0;
            }
        }
    }
    
    fclose(fp);
    return 1;
}

// Detect Python version from source tree
void detect_python_version(python_source_context* ctx) {
    char version_path[512];
    snprintf(version_path, sizeof(version_path), "%s/Include/patchlevel.h", ctx->python_root_path);
    
    FILE* fp = fopen(version_path, "r");
    if (!fp) {
        strcpy(ctx->python_version, "unknown");
        return;
    }
    
    char line[MAX_LINE_LENGTH];
    int major = 0, minor = 0, micro = 0;
    
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "PY_MAJOR_VERSION")) {
            sscanf(line, "#define PY_MAJOR_VERSION %d", &major);
        } else if (strstr(line, "PY_MINOR_VERSION")) {
            sscanf(line, "#define PY_MINOR_VERSION %d", &minor);
        } else if (strstr(line, "PY_MICRO_VERSION")) {
            sscanf(line, "#define PY_MICRO_VERSION %d", &micro);
        }
    }
    
    snprintf(ctx->python_version, sizeof(ctx->python_version), "%d.%d.%d", major, minor, micro);
    fclose(fp);
}

// Initialize Python source analysis context
python_source_context* init_python_source_context(const char* python_root_path) {
    python_source_context* ctx = (python_source_context*)malloc(sizeof(python_source_context));
    memset(ctx, 0, sizeof(python_source_context));
    
    ctx->python_root_path = strdup(python_root_path);
    
    // Verify the path exists
    struct stat st;
    if (stat(python_root_path, &st) != 0 || !S_ISDIR(st.st_mode)) {
        printf("ERROR: Python source path does not exist: %s\n", python_root_path);
        free(ctx);
        return NULL;
    }
    
    // Detect Python version
    detect_python_version(ctx);
    printf("Detected Python version: %s\n", ctx->python_version);
    
    // Parse opcode definitions
    if (!parse_opcode_definitions(ctx)) {
        free(ctx);
        return NULL;
    }
    
    // Parse stack effects
    parse_stack_effects(ctx);
    
    return ctx;
}

// Find opcode info by opcode number
opcode_info* find_opcode_info(python_source_context* ctx, int opcode) {
    for (int i = 0; i < ctx->opcode_count; i++) {
        if (ctx->opcodes[i].opcode == opcode) {
            return &ctx->opcodes[i];
        }
    }
    return NULL;
}

// Create a simplified atom info structure (not the full source_atom yet)
typedef struct simple_atom_info {
    int atom_type;
    py_instruction* inst;
    opcode_info* op_info;
} simple_atom_info;

simple_atom_info* create_atom_info_from_opcode(opcode_info* info, py_instruction* inst) {
    simple_atom_info* atom_info = (simple_atom_info*)malloc(sizeof(simple_atom_info));
    memset(atom_info, 0, sizeof(simple_atom_info));
    
    atom_info->inst = inst;
    atom_info->op_info = info;
    
    if (!info) {
        atom_info->atom_type = 0; // DUMMY
        return atom_info;
    }
    
    // Map based on opcode category (using numbers instead of enum constants for now)
    switch (info->category) {
        case 1: // Binary operations
            atom_info->atom_type = 1; // BINARYOPS
            break;
            
        case 2: // Unary operations  
            atom_info->atom_type = 2; // UNARYOPS
            break;
            
        case 3: // Load operations
            atom_info->atom_type = 3; // STR/LOAD
            break;
            
        case 4: // Store operations
            atom_info->atom_type = 4; // STORE_VAR
            break;
            
        case 5: // Call operations
            atom_info->atom_type = 5; // CALLFUNCTION
            break;
            
        case 6: // Build operations
            if (strstr(info->name, "LIST")) {
                atom_info->atom_type = 6; // LIST
            } else if (strstr(info->name, "TUPLE")) {
                atom_info->atom_type = 7; // TUPLE
            } else if (strstr(info->name, "SET")) {
                atom_info->atom_type = 8; // BUILDSET
            } else if (strstr(info->name, "MAP")) {
                atom_info->atom_type = 8; // BUILDSET (Dictionary)
            } else {
                atom_info->atom_type = 9; // COLLECTION
            }
            break;
            
        default:
            // Handle special cases by name
            if (strstr(info->name, "RETURN")) {
                atom_info->atom_type = 10; // RETURN
            } else if (strstr(info->name, "JUMP")) {
                atom_info->atom_type = 11; // JUMP
            } else if (strstr(info->name, "COMPARE")) {
                atom_info->atom_type = 12; // COMPARE
            } else if (strstr(info->name, "SLICE")) {
                atom_info->atom_type = 13; // SLICE
            } else {
                atom_info->atom_type = 0; // DUMMY
            }
            break;
    }
    
    return atom_info;
}

// Find overlapping atoms - atoms that span the same bytecode regions
void find_atom_overlaps(atom_extraction_result* result) {
    for (int i = 0; i < result->mapping_count; i++) {
        bytecode_atom_mapping* mapping = &result->mappings[i];
        mapping->overlapping_atoms = (bytecode_atom_mapping**)malloc(sizeof(bytecode_atom_mapping*) * result->mapping_count);
        mapping->overlaps_count = 0;
        
        for (int j = 0; j < result->mapping_count; j++) {
            if (i == j) continue;
            
            bytecode_atom_mapping* other = &result->mappings[j];
            
            // Check if bytecode ranges overlap
            if (mapping->start_offset < other->end_offset && 
                mapping->end_offset > other->start_offset) {
                
                mapping->overlapping_atoms[mapping->overlaps_count++] = other;
            }
        }
    }
}

// Simplified stub that demonstrates the concept
void gen_source_obj_dynamic(python_source_context* ctx, py_function* fn, int idx, 
                           source_atom_tree* atoms, source_atom* out) {
    py_instruction* inst = &fn->instruction_set[idx];
    opcode_info* info = find_opcode_info(ctx, inst->opcode);
    
    if (!info) {
        printf("WARNING: Unknown opcode %d at offset %d\n", inst->opcode, inst->off);
        out->type = SOURCE_ATOM_DUMMY;
        out->len = 1;
        out->inst = inst;
        return;
    }
    
    // Demonstrate dynamic opcode detection
    printf("Dynamic: Processing opcode %s (%d) category %d at offset %d\n", 
           info->name, info->opcode, info->category, inst->off);
    
    // Simple mapping based on opcode category
    switch (info->category) {
        case 1: // Binary operations
            out->type = SOURCE_ATOM_BINARYOPS;
            break;
        case 5: // Call operations  
            out->type = SOURCE_ATOM_CALLFUNCTION;
            break;
        case 6: // Build operations
            if (strstr(info->name, "LIST")) {
                out->type = SOURCE_ATOM_LIST;
            } else if (strstr(info->name, "TUPLE")) {
                out->type = SOURCE_ATOM_TUPLE;
            } else {
                out->type = SOURCE_ATOM_COLLECTION;
            }
            break;
        case 3: // Load operations
            out->type = SOURCE_ATOM_STR;
            break;
        case 4: // Store operations
            out->type = SOURCE_ATOM_STORE_VAR;
            break;
        default:
            out->type = SOURCE_ATOM_DUMMY;
            break;
    }
    
    out->len = 1;
    out->inst = inst;
    out->data = NULL; // Simplified - would need proper data structures
    
    printf("  -> Mapped to atom type %d\n", out->type);
}

// Main extraction function - now properly integrated
atom_extraction_result* extract_atoms_from_bytecode(python_source_context* ctx,
                                                   py_instruction* bytecode_array,
                                                   int bytecode_count) {
    printf("Python source context initialized for version %s with %d opcodes\n", 
           ctx->python_version, ctx->opcode_count);
    
    atom_extraction_result* result = (atom_extraction_result*)malloc(sizeof(atom_extraction_result));
    memset(result, 0, sizeof(atom_extraction_result));
    
    // This would be called from the existing decompiler framework
    // For now, return a stub result
    result->atoms = (source_atom**)malloc(sizeof(source_atom*) * bytecode_count);
    result->mappings = (bytecode_atom_mapping*)malloc(sizeof(bytecode_atom_mapping) * bytecode_count);
    result->atom_count = 0;
    result->mapping_count = 0;
    
    return result;
}

// Cleanup
void cleanup_extraction_result(atom_extraction_result* result) {
    if (!result) return;
    
    for (int i = 0; i < result->mapping_count; i++) {
        free(result->mappings[i].overlapping_atoms);
    }
    
    free(result->atoms);
    free(result->mappings);
    free(result);
}

void cleanup_python_source_context(python_source_context* ctx) {
    if (!ctx) return;
    
    free(ctx->opcodes);
    free(ctx->python_root_path);
    free(ctx);
}