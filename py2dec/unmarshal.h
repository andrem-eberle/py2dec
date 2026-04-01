#pragma once
#include "common.h"

#define TYPE_NULL               '0'
#define TYPE_NONE               'N'
#define TYPE_FALSE              'F'
#define TYPE_TRUE               'T'
#define TYPE_STOPITER           'S'
#define TYPE_ELLIPSIS           '.'
#define TYPE_INT                'i'
#define TYPE_INT64              'I'
#define TYPE_FLOAT              'f'
#define TYPE_BINARY_FLOAT       'g'
#define TYPE_COMPLEX            'x'
#define TYPE_BINARY_COMPLEX     'y'
#define TYPE_LONG               'l'
#define TYPE_STRING             's'
#define TYPE_INTERNED           't'
#define TYPE_STRINGREF          'R'
#define TYPE_TUPLE              '('
#define TYPE_LIST               '['
#define TYPE_DICT               '{'
#define TYPE_CODE               'c'
#define TYPE_UNICODE            'u'
#define TYPE_UNKNOWN            '?'
#define TYPE_SET                '<'
#define TYPE_FROZENSET          '>'

typedef struct un_type {
	int type;
} un_type;

typedef struct un_str {
	un_type type;
	un_str(char * istr, int isize) {
		type.type = TYPE_STRING;
		size = isize;
		str = istr;
	}
	int size;
	char * str;
} un_str;

typedef struct unmarshal_bytes {
	byte * st;
	byte * current;
	byte * lim;

	un_str ** str_ref;
	int str_ref_sz;
	int str_ref_fsz;

	uint64 get_longlong() {
		uint64 t = *(uint64*)current;
		current += 8;
		return t;
	}

	uint32 get_long() {
		uint32 t = *(uint32*)current;
		current += 4;
		return t;
	}

	uint32 get_byte() {
		uint32 t = *(byte*)current;
		current++;
		return t;
	}

	uint32 get_short() {
		uint32 t = *(uint16*)current;
		current += 2;
		return t;
	}

	double get_double() {
		double t = *(double*)current;
		current += 8;
		return t;
	}

	void skip(int n) {
		current += n;
	}

	void ref_str(un_str * str) {
		if (str_ref_fsz == 0) {
			str_ref_fsz = 4;
			str_ref = (un_str**)calloc(1, str_ref_fsz * sizeof(un_str*));
		}
		else if (str_ref_sz == str_ref_fsz) {
			str_ref_fsz *= 2;
			un_str ** old = str_ref;
			str_ref = (un_str**)calloc(1, str_ref_fsz * sizeof(char*));
			memcpy(str_ref, old, str_ref_sz * sizeof(char*));
			free(old);
		}

		str_ref[str_ref_sz++] = str;
	}

} unmarshal_bytes;

typedef struct un_none {
	un_type type;
	un_none() {
		type.type = TYPE_NONE;
	}
} un_none;

typedef struct un_true_st {
	un_type type;
	int val;
	un_true_st() {
		type.type = TYPE_TRUE;
	}
} un_true_st;

typedef struct un_false_st {
	un_type type;
	int val;
	un_false_st() {
		type.type = TYPE_FALSE;
	}
} un_false_st;

typedef struct un_tuple {
	un_type type;
	int size;
	void ** data;
	un_tuple() {
		type.type = TYPE_TUPLE;
	}
	un_tuple(int isize) {
		type.type = TYPE_TUPLE;
		size = isize;
		data = new void*[isize];
	}
	~un_tuple() {
		if (data) {
			delete[] data;
		}
		
	}
} un_tuple;

typedef struct un_code {
	un_type type;
	uint32 argcount;
	uint32 nlocals;
	uint32 stacksize;
	uint32 flags;
	void * code;

	un_tuple *consts;
	un_tuple *names;
	un_tuple *varnames;
	un_tuple *freevars;
	un_tuple *cellvars;
	void *filename;
	void *name;
	uint32 firstlineno;
	void * lnotab;
	un_code() {
		memset(this, 0, sizeof(un_code));
		type.type = TYPE_CODE;
	}

	~un_code() {
		if (name) delete name;
		if (filename) delete filename;
	}

} un_code;

typedef struct un_long {
	un_type type;
	int64 val;
	int sign;
	un_long() {
		sign = 1;
		type.type = TYPE_LONG;
	}
} un_long;

typedef struct un_longlong {
	un_type type;
	int64 val;
	un_longlong() {
		type.type = TYPE_INT64;
	}
} un_longlong;

typedef struct un_int {
	un_type type;
	uint32 val;
	un_int() {
		type.type = TYPE_INT;
	}
} un_int;

typedef struct un_double {
	un_type type;
	double val;
	un_double() {
		type.type = TYPE_FLOAT;
	}
} un_double;

typedef struct un_unicode {
	un_type type;
	char * original_bytes;
	un_unicode() {
		type.type = TYPE_UNICODE;
	}
} un_unicode;

typedef struct un_stringref {
	un_type type;
	int val;
	un_str * ref;
	
} un_stringref;

typedef struct un_complex {
	un_type type;
	double real;
	double imaginary;
	un_complex() {
		type.type = TYPE_BINARY_COMPLEX;
	}
} un_complex;

typedef void * (*un_fn)(unmarshal_bytes * m);

void init_unmarshal();
int unmarshal_from_bytes(byte * data, int sz, un_type ** out);
un_complex * un_coerce_complex(void * arg);
un_tuple * un_coerce_tuple(void * arg);
un_unicode * un_coerce_unicode(void * arg);
un_str * un_coerce_str(void * arg);
un_str * un_resolve_strref(void * arg);
un_double * un_coerce_double(void * arg);
un_code * un_coerce_code(void * arg);
char * un_resolve_str(void * arg);
un_str * un_reduce_str(void * arg);
char * un_to_printable(char * out, void * arg);
int un_str_size(void * arg);
int64 un_resolve_int(void * arg);

void un_dump_code(un_code * c);
char * un_dump_object(char * out, void * arg);
