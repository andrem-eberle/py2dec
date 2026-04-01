#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <sys/stat.h>
#include "common.h"
#include "opcodes.h"
#include "disasm.h"
#include "py_gen.h"

#define MAX_PATTERNS 1000
#define MAX_OPCODES_PER_PATTERN 20
#define MAX_FUNCTION_NAME 128
#define MAX_OPCODE_SEQUENCE 512

typedef enum ast_node_type {
    AST_PROGRAM = 1,
    AST_BINARY_OP,
    AST_UNARY_OP,
    AST_FUNCTION_CALL,
    AST_LIST_LITERAL,
    AST_TUPLE_LITERAL,
    AST_DICT_LITERAL,
    AST_LIST_COMPREHENSION,
    AST_DICT_COMPREHENSION,
    AST_IF_STATEMENT,
    AST_FOR_LOOP,
    AST_WHILE_LOOP,
    AST_IDENTIFIER,
    AST_STRING_LITERAL,
    AST_NUMBER_LITERAL,
    AST_ATTRIBUTE_ACCESS,
    AST_SUBSCRIPT,
    AST_SLICE,
    AST_ASSIGNMENT,
    AST_RETURN_STATEMENT,
    AST_IMPORT_STATEMENT,
    AST_CLASS_DEFINITION,
    AST_FUNCTION_DEFINITION,
    AST_LAMBDA,
    AST_UNKNOWN
} ast_node_type;

typedef struct opcode_pattern {
    int opcode;           // Specific opcode or -1 for wildcard
    int arg_constraint;   // Argument constraint or -1 for any
    char* name_pattern;   // String pattern for opcode name matching
} opcode_pattern;

typedef struct compilation_pattern {
    char function_name[MAX_FUNCTION_NAME];     // e.g., "compiler_binop"
    opcode_pattern opcodes[MAX_OPCODES_PER_PATTERN];
    int opcode_count;
    ast_node_type ast_type;
    int priority;         // Higher priority patterns match first
    char description[256];
} compilation_pattern;

typedef struct ast_node {
    ast_node_type type;
    void* data;
    py_instruction* source_insts;  // Source bytecode instructions
    int source_count;
    struct ast_node** children;
    int children_count;
    int children_capacity;
} ast_node;

typedef struct python_ast_parser {
    char* python_root_path;
    compilation_pattern* patterns;
    int pattern_count;
    char python_version[32];
} python_ast_parser;

// Extract compiler function patterns from Python's compile.c
int parse_compiler_function(FILE* fp, const char* function_name, compilation_pattern* pattern) {
    char line[1024];
    regex_t addop_regex, visit_regex;
    regmatch_t matches[3];
    int in_function = 0;
    int brace_depth = 0;
    
    // Compile regexes for different opcode emission patterns
    regcomp(&addop_regex, "ADDOP\\(c,\\s*([A-Z_]+)\\)", REG_EXTENDED);
    regcomp(&visit_regex, "VISIT\\(c,\\s*expr,", REG_EXTENDED);
    
    pattern->opcode_count = 0;
    strcpy(pattern->function_name, function_name);
    
    // Seek to function start
    fseek(fp, 0, SEEK_SET);
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, function_name) && strstr(line, "static int")) {
            in_function = 1;
            printf("Found function: %s\n", function_name);
            break;
        }
    }
    
    if (!in_function) {
        regfree(&addop_regex);
        regfree(&visit_regex);
        return 0;
    }
    
    // Parse function body for opcode patterns
    while (fgets(line, sizeof(line), fp) && pattern->opcode_count < MAX_OPCODES_PER_PATTERN) {
        // Track brace depth to know when function ends
        for (char* c = line; *c; c++) {
            if (*c == '{') brace_depth++;
            if (*c == '}') brace_depth--;
        }
        
        if (brace_depth < 0) break; // Function ended
        
        // Look for VISIT(c, expr, ...) - these generate LOAD operations
        if (regexec(&visit_regex, line, 0, NULL, 0) == 0) {
            opcode_pattern* op = &pattern->opcodes[pattern->opcode_count++];
            op->opcode = -1;  // Wildcard - will be LOAD_*
            op->arg_constraint = -1;
            op->name_pattern = strdup("LOAD_*");
            printf("  Found VISIT -> LOAD_* pattern\n");
        }
        
        // Look for ADDOP(c, OPCODE_NAME) - these are specific opcodes
        if (regexec(&addop_regex, line, 3, matches, 0) == 0) {
            char opcode_name[64];
            int len = matches[1].rm_eo - matches[1].rm_so;
            strncpy(opcode_name, line + matches[1].rm_so, len);
            opcode_name[len] = '\0';
            
            opcode_pattern* op = &pattern->opcodes[pattern->opcode_count++];
            op->opcode = -1;  // Would need opcode name->number lookup
            op->arg_constraint = -1;
            op->name_pattern = strdup(opcode_name);
            printf("  Found ADDOP -> %s pattern\n", opcode_name);
        }
    }
    
    regfree(&addop_regex);
    regfree(&visit_regex);
    
    if (pattern->opcode_count > 0) {
        printf("Extracted pattern with %d opcodes from %s\n", pattern->opcode_count, function_name);
        return 1;
    }
    
    return 0;
}

// Extract all compilation patterns from Python source
int extract_patterns_from_python_source(python_ast_parser* parser) {
    char compile_path[512];
    snprintf(compile_path, sizeof(compile_path), "%s/Python/compile.c", parser->python_root_path);
    
    FILE* fp = fopen(compile_path, "r");
    if (!fp) {
        printf("ERROR: Could not open compile.c at %s\n", compile_path);
        return 0;
    }
    
    parser->patterns = (compilation_pattern*)malloc(sizeof(compilation_pattern) * MAX_PATTERNS);
    parser->pattern_count = 0;
    
    // List of compiler functions to extract patterns from
    const char* compiler_functions[] = {
        "compiler_binop",      // Binary operations: a + b, a * b, etc.
        "compiler_unaryop",    // Unary operations: -a, not a, etc.
        "compiler_call",       // Function calls: f(a, b)
        "compiler_listcomp",   // List comprehensions: [x for x in items]
        "compiler_dictcomp",   // Dict comprehensions: {k: v for k, v in items}
        "compiler_setcomp",    // Set comprehensions: {x for x in items}
        "compiler_compare",    // Comparisons: a == b, a < b, etc.
        "compiler_ifexp",      // Conditional expressions: a if b else c
        "compiler_lambda",     // Lambda functions: lambda x: x + 1
        "compiler_if",         // If statements
        "compiler_for",        // For loops
        "compiler_while",      // While loops
        "compiler_assign",     // Assignments: a = b
        "compiler_augassign",  // Augmented assignments: a += b
        "compiler_return",     // Return statements
        "compiler_import",     // Import statements
        "compiler_from",       // From imports
        "compiler_assert",     // Assert statements
        "compiler_raise",      // Raise statements
        "compiler_try",        // Try/except blocks
        "compiler_with",       // With statements
        NULL
    };
    
    for (int i = 0; compiler_functions[i]; i++) {
        compilation_pattern pattern;
        memset(&pattern, 0, sizeof(pattern));
        
        if (parse_compiler_function(fp, compiler_functions[i], &pattern)) {
            // Map function name to AST type
            if (strstr(pattern.function_name, "binop")) {
                pattern.ast_type = AST_BINARY_OP;
                pattern.priority = 10;
                strcpy(pattern.description, "Binary operation (a + b, a * b, etc.)");
            } else if (strstr(pattern.function_name, "call")) {
                pattern.ast_type = AST_FUNCTION_CALL;
                pattern.priority = 20;
                strcpy(pattern.description, "Function call f(args)");
            } else if (strstr(pattern.function_name, "listcomp")) {
                pattern.ast_type = AST_LIST_COMPREHENSION;
                pattern.priority = 30;
                strcpy(pattern.description, "List comprehension [x for x in items]");
            } else if (strstr(pattern.function_name, "if")) {
                pattern.ast_type = AST_IF_STATEMENT;
                pattern.priority = 25;
                strcpy(pattern.description, "If statement");
            } else {
                pattern.ast_type = AST_UNKNOWN;
                pattern.priority = 5;
                strcpy(pattern.description, "Unknown construct");
            }
            
            parser->patterns[parser->pattern_count++] = pattern;
        }
    }
    
    fclose(fp);
    
    printf("Extracted %d compilation patterns from Python %s\n", 
           parser->pattern_count, parser->python_version);
    
    return parser->pattern_count > 0;
}

// Match bytecode sequence against a pattern
int match_pattern(py_instruction* opcodes, int available, compilation_pattern* pattern) {
    if (available < pattern->opcode_count) {
        return 0;
    }
    
    for (int i = 0; i < pattern->opcode_count; i++) {
        opcode_pattern* op_pattern = &pattern->opcodes[i];
        py_instruction* inst = &opcodes[i];
        
        // Wildcard match
        if (op_pattern->opcode == -1) {
            if (op_pattern->name_pattern && strstr(op_pattern->name_pattern, "LOAD_")) {
                // Check if this is actually a load operation
                if (inst->opcode < LOAD_CONST || inst->opcode > LOAD_DEREF) {
                    return 0;  // Not a load operation
                }
            }
            continue;
        }
        
        // Exact opcode match
        if (op_pattern->opcode != inst->opcode) {
            return 0;
        }
        
        // Argument constraint match
        if (op_pattern->arg_constraint != -1 && op_pattern->arg_constraint != inst->arg) {
            return 0;
        }
    }
    
    return pattern->opcode_count;  // Number of instructions consumed
}

// Build AST node from matched pattern
ast_node* build_ast_node(py_instruction* opcodes, int consumed, compilation_pattern* pattern) {
    ast_node* node = (ast_node*)malloc(sizeof(ast_node));
    memset(node, 0, sizeof(ast_node));
    
    node->type = pattern->ast_type;
    node->source_insts = opcodes;
    node->source_count = consumed;
    node->children_capacity = 8;
    node->children = (ast_node**)malloc(sizeof(ast_node*) * node->children_capacity);
    
    printf("Built AST node: %s (consumed %d opcodes)\n", pattern->description, consumed);
    
    return node;
}

// Main AST recognition function
ast_node* recognize_ast_patterns(python_ast_parser* parser, py_instruction* opcodes, int count) {
    ast_node* root = (ast_node*)malloc(sizeof(ast_node));
    memset(root, 0, sizeof(ast_node));
    root->type = AST_PROGRAM;
    root->children_capacity = 16;
    root->children = (ast_node**)malloc(sizeof(ast_node*) * root->children_capacity);
    
    printf("Starting AST pattern recognition on %d instructions\n", count);
    
    for (int i = 0; i < count; ) {
        bool matched = false;
        int best_consumed = 0;
        compilation_pattern* best_pattern = NULL;
        
        // Try all patterns, find the best match (highest priority, most consumed)
        for (int p = 0; p < parser->pattern_count; p++) {
            compilation_pattern* pattern = &parser->patterns[p];
            
            int consumed = match_pattern(opcodes + i, count - i, pattern);
            if (consumed > 0) {
                if (!matched || consumed > best_consumed || pattern->priority > best_pattern->priority) {
                    best_consumed = consumed;
                    best_pattern = pattern;
                    matched = true;
                }
            }
        }
        
        if (matched) {
            ast_node* node = build_ast_node(opcodes + i, best_consumed, best_pattern);
            
            // Add to root children
            if (root->children_count >= root->children_capacity) {
                root->children_capacity *= 2;
                root->children = (ast_node**)realloc(root->children, 
                    sizeof(ast_node*) * root->children_capacity);
            }
            root->children[root->children_count++] = node;
            
            i += best_consumed;
        } else {
            printf("WARNING: No pattern matched at instruction %d (opcode %d)\n", 
                   i, opcodes[i].opcode);
            i++;  // Skip unrecognized instruction
        }
    }
    
    printf("AST recognition complete: %d top-level nodes\n", root->children_count);
    return root;
}

// Initialize Python AST parser
python_ast_parser* init_python_ast_parser(const char* python_root_path) {
    python_ast_parser* parser = (python_ast_parser*)malloc(sizeof(python_ast_parser));
    memset(parser, 0, sizeof(python_ast_parser));
    
    parser->python_root_path = strdup(python_root_path);
    
    // Verify Python source exists
    struct stat st;
    if (stat(python_root_path, &st) != 0 || !S_ISDIR(st.st_mode)) {
        printf("ERROR: Python source path does not exist: %s\n", python_root_path);
        free(parser);
        return NULL;
    }
    
    // Detect Python version
    char version_path[512];
    snprintf(version_path, sizeof(version_path), "%s/Include/patchlevel.h", python_root_path);
    
    FILE* fp = fopen(version_path, "r");
    if (fp) {
        char line[256];
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
        
        snprintf(parser->python_version, sizeof(parser->python_version), "%d.%d.%d", major, minor, micro);
        fclose(fp);
    } else {
        strcpy(parser->python_version, "unknown");
    }
    
    printf("Initializing AST parser for Python %s\n", parser->python_version);
    
    // Extract compilation patterns from Python source
    if (!extract_patterns_from_python_source(parser)) {
        printf("ERROR: Failed to extract patterns from Python source\n");
        free(parser);
        return NULL;
    }
    
    return parser;
}

// Cleanup
void cleanup_python_ast_parser(python_ast_parser* parser) {
    if (!parser) return;
    
    if (parser->patterns) {
        for (int i = 0; i < parser->pattern_count; i++) {
            for (int j = 0; j < parser->patterns[i].opcode_count; j++) {
                free(parser->patterns[i].opcodes[j].name_pattern);
            }
        }
        free(parser->patterns);
    }
    
    free(parser->python_root_path);
    free(parser);
}

void cleanup_ast_node(ast_node* node) {
    if (!node) return;
    
    for (int i = 0; i < node->children_count; i++) {
        cleanup_ast_node(node->children[i]);
    }
    
    free(node->children);
    free(node);
}

// Debug: Print AST tree
void print_ast_tree(ast_node* node, int depth) {
    if (!node) return;
    
    const char* type_names[] = {
        "PROGRAM", "BINARY_OP", "UNARY_OP", "FUNCTION_CALL", "LIST_LITERAL",
        "TUPLE_LITERAL", "DICT_LITERAL", "LIST_COMPREHENSION", "DICT_COMPREHENSION",
        "IF_STATEMENT", "FOR_LOOP", "WHILE_LOOP", "IDENTIFIER", "STRING_LITERAL",
        "NUMBER_LITERAL", "ATTRIBUTE_ACCESS", "SUBSCRIPT", "SLICE", "ASSIGNMENT",
        "RETURN_STATEMENT", "IMPORT_STATEMENT", "CLASS_DEFINITION", "FUNCTION_DEFINITION",
        "LAMBDA", "UNKNOWN"
    };
    
    for (int i = 0; i < depth; i++) printf("  ");
    printf("%s", type_names[node->type - 1]);
    
    if (node->source_count > 0) {
        printf(" [%d opcodes]", node->source_count);
    }
    
    printf("\n");
    
    for (int i = 0; i < node->children_count; i++) {
        print_ast_tree(node->children[i], depth + 1);
    }
}

#ifdef TEST_AST_PARSER
int main(int argc, char** argv) {
    printf("=== Python AST Parser Test ===\n\n");
    
    // Check command line arguments
    if (argc < 3) {
        printf("Usage: %s <path_to_python_source> <pyc_file>\n", argv[0]);
        printf("Example: %s /usr/src/python3.12 test.pyc\n", argv[0]);
        return 1;
    }
    
    const char* python_path = argv[1];
    const char* pyc_file = argv[2];
    
    printf("Python source: %s\n", python_path);
    printf("PYC file: %s\n\n", pyc_file);
    
    // Initialize parser with Python source
    python_ast_parser* parser = init_python_ast_parser(python_path);
    if (!parser) {
        printf("FAILED: Could not initialize AST parser\n");
        return 1;
    }
    
    printf("\n=== Pattern Extraction Results ===\n");
    for (int i = 0; i < parser->pattern_count; i++) {
        compilation_pattern* p = &parser->patterns[i];
        printf("Pattern %d: %s -> %s (priority %d)\n", i + 1, p->function_name, p->description, p->priority);
        printf("  Opcodes: ");
        for (int j = 0; j < p->opcode_count; j++) {
            if (p->opcodes[j].name_pattern) {
                printf("%s ", p->opcodes[j].name_pattern);
            } else {
                printf("UNKNOWN ");
            }
        }
        printf("\n\n");
    }
    
    // TODO: Load and parse the PYC file to get real bytecode instructions
    printf("=== Loading PYC File ===\n");
    printf("TODO: Parse %s and extract bytecode instructions\n", pyc_file);
    printf("TODO: Feed bytecode to recognize_ast_patterns()\n");
    printf("TODO: Output reconstructed AST\n\n");
    
    // Cleanup
    cleanup_python_ast_parser(parser);
    
    printf("=== Test Complete ===\n");
    return 0;
}
#endif