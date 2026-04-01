#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "log.h"

#ifdef _WIN32
#include <Windows.h>
#endif

#include "global_config.h"

#define pylog(...)

typedef unsigned char byte;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef int int32;
typedef unsigned long long uint64;
typedef long long int64;

void escape_regular_string(char * dst, char * str);
void init_strings();
void py_assert1(char * file, int line, int val, char * msg,...);
#define py_assert(v,m,...) py_assert1(__FILE__,__LINE__,v,m,##__VA_ARGS__)
void init_opcode_map();
int num_len(uint32 val);
char * opcode_to_str(int opcode);
void unicode_to_ascii(char * out, char * bytes);




char * right_sprint_num(char * out, int val, int max_len);

#define linked_list_insert(h,t,o,c) \
if (!(h)) { \
	(h) = (t) = (o); \
} \
else { \
	(t)->next = (o); \
	(t) = (t)->next; \
} \
(c)++;
