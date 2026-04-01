#include "common.h"
#include "unmarshal.h"


un_none local_none = un_none();
un_false_st un_false = un_false_st();
un_true_st un_true = un_true_st();
un_fn unmarshal_map[256] = { 0, };


static void * unmarshal_load(unmarshal_bytes * m) {
	uint32 c = m->get_byte();
	py_assert(unmarshal_map[c] != NULL, "Unimplemented marshal %c (%X) \n", c, c);
		
	un_type * rt = (un_type*)unmarshal_map[c](m);
	if (!rt) {
		return rt;
	}
	py_assert(rt->type != 0, "Bad unmarshall type zero, type was %c",c);

	return rt;
}

static void * null_fn(unmarshal_bytes * m) {
	return NULL;
}

static void * stop_iteration_fn(unmarshal_bytes * m) {
	return NULL;
}

static void * ellipsis_fn(unmarshal_bytes * m) {
	return NULL;
}

#define SIZE32_MAX  0x7FFFFFFF

static void * str_fn(unmarshal_bytes * m) {
	uint32 size = m->get_long();
	uint32 max_size = SIZE32_MAX;
	
	if (size > max_size) {
		printf("Bad marshal string size: %i, max: %i\n",size,max_size);
		return NULL;
	}

	char * str = (char *)calloc(1,size+1);
	memcpy(str, m->current, size);
	m->skip(size);
	
	return new un_str(str,size);
}

static void * intstr_fn(unmarshal_bytes * m) {
	uint32 size = m->get_long();
	
	if (size > SIZE32_MAX) {
		printf("bad marshal string\n");
		return NULL;
	}

	
	char * str = (char *)calloc(1, size + 1);
	memcpy(str, m->current, size);
	//printf("intern string %s\n", str);
	m->skip(size);
	un_str * s = new un_str(str, size);
	m->ref_str(s);

	return s;
}

void * code_fn(unmarshal_bytes * m) {
	un_code * cc = new un_code();
	
	cc->argcount = m->get_long();
	cc->nlocals = m->get_long();
	cc->stacksize = m->get_long();
	cc->flags = m->get_long();
	
	if (!(cc->code = unmarshal_load(m))) {
		delete cc;
		return NULL;
	}

	cc->consts = (un_tuple*)unmarshal_load(m);
	un_tuple * tconsts = cc->consts;
	int i;

	for (i = 0; i < tconsts->size; i++) {
		un_type * t = (un_type*)tconsts->data[i];		
		if (t->type == 's') {
			un_str * str = (un_str*)t;
		}
	}
	
	if (cc->consts == NULL) {
		delete cc;
		return NULL;
	}
	cc->names = (un_tuple*) unmarshal_load(m);
	if (cc->names == NULL) {
		delete cc;
		return NULL;
	}
	py_assert(cc->names->type.type == TYPE_TUPLE, "Bad code object");
	cc->varnames = (un_tuple*)unmarshal_load(m);
	if (cc->varnames == NULL) {
		delete cc;
		return NULL;
	}
	py_assert(cc->varnames->type.type == TYPE_TUPLE, "Bad code object");
		
	cc->freevars = (un_tuple*)unmarshal_load(m);
	if (cc->freevars == NULL) {
		delete cc;
		return NULL;
	}
	py_assert(cc->freevars->type.type == TYPE_TUPLE, "Bad code object");
		
	cc->cellvars =  un_coerce_tuple(unmarshal_load(m));
	if (cc->cellvars == NULL) {
		delete cc;
		return NULL;
	}
		
	cc->filename = unmarshal_load(m);
	if (cc->filename == NULL) {
		delete cc;
		return NULL;
	}
		
	cc->name = unmarshal_load(m);
	if (cc->name == NULL) {
		delete cc;
		return NULL;
	}

		
	cc->firstlineno = m->get_long();
	cc->lnotab = unmarshal_load(m);
	if (!cc->lnotab) return NULL;

	return cc;
	
}

void * none_fn(unmarshal_bytes * m) {
	return &local_none;
}

void * longint_fn(unmarshal_bytes * m) {
	
	un_longlong *l = new un_longlong();
	l->val = m->get_longlong();
	return l;
}

void * int_fn(unmarshal_bytes * m) {	
	
	un_long * l = new un_long();
	l->val = (int)m->get_long();
	return l;
}

void * unicode_fn(unmarshal_bytes * m) {
	un_unicode * u = new un_unicode();
	int size = m->get_long();
	
	u->original_bytes = new char[size+1];

	memset(u->original_bytes, 0, size + 1);	
	if (size > 0) {
		memcpy(u->original_bytes, m->current, size);

		m->skip(size);
	}
	return u;
}

// from python 2.7.18 source
#define PyLong_SHIFT	30
#define PyLong_MARSHAL_SHIFT 15
#define PyLong_MARSHAL_BASE ((short)1 << PyLong_MARSHAL_SHIFT)
#define PyLong_MARSHAL_RATIO (PyLong_SHIFT / PyLong_MARSHAL_SHIFT)

void *bin_complex_fn(unmarshal_bytes * m) {
	un_complex * c = new un_complex();
	c->real = m->get_double();
	c->imaginary = m->get_double();
	return c;
}

uint64 p2(uint64 exp) {
	uint64 s = 1;
	int i;
	for (i = 0; i < exp; i++) {
		s *= 2;
	}
	return s;
}

uint64 abs1(int64 x) {
	if (x < 0) {
		return x;
	}
	return x;
}

void *long_fn(unmarshal_bytes * m) {
	
	int32 nx = (int32) m->get_long();
	un_long * l = new un_long();
	
	uint64 n = abs(nx);
	
	if (n == 0) {
		l->val = 0;
		return l;
	}
	int size = 1 + (n - 1) / PyLong_MARSHAL_RATIO;

	if (nx < 0) {
		l->sign = -1;
	}

	int shorts_in_top_digit = 1 + (n - 1) % PyLong_MARSHAL_RATIO;
	
	int i, j;
	uint64 d;
	uint64 md;
	int digits[32];
	
	for (i = 0; i < size - 1; i++) {
		d = 0;
		for (j = 0; j < PyLong_MARSHAL_RATIO; j++) {
			md = m->get_short();
			py_assert(md >= 0 && md < PyLong_MARSHAL_BASE, "Unknown marshal digit");
			d += md << j*PyLong_MARSHAL_SHIFT;
		}
		digits[i] = d;
	}
	d = 0;
	for (j = 0; j < shorts_in_top_digit; j++) {
		md = m->get_short();	

		py_assert(md >= 0 && md < PyLong_MARSHAL_BASE, "Unknown marshal digit");

		if (md == 0 && j == shorts_in_top_digit - 1) {			
			py_assert(0,"bad marshal data (unnormalized long data) %i %i",j, shorts_in_top_digit);
			return NULL;
		}
		d += md << j*PyLong_MARSHAL_SHIFT;

	}
	
	digits[size - 1] = d;
	uint64 out = 0;
	for (i = 0; i < size; i++) {
		out += digits[i] * p2(PyLong_SHIFT*i);
	}
	l->val = out;

	return l;
}

void * binfloat_fn(unmarshal_bytes * m) {
	double d = m->get_double();
	un_double * dd = new un_double();
	dd->val = d;
	return dd;
}

void * stringref_fn(unmarshal_bytes * m) {
	int n = m->get_long();
	un_stringref * ref = (un_stringref*)calloc(1,sizeof(un_stringref));
	ref->type.type = TYPE_STRINGREF;
	ref->val = n;
	//printf("%i\n", n);
	if (n >= m->str_ref_sz) {
		printf("bad str ref in marshal\n");
		return NULL;
	}
	ref->ref = m->str_ref[n];

	return ref;
}

void * tuple_fn(unmarshal_bytes * m) {
	uint32 size = m->get_long();
	if (size > SIZE32_MAX) {
		printf("bad tuple on unmarshal\n");
		return NULL;
	}
	int i;
	un_tuple * tuple = new un_tuple();
	tuple->size = size;
	
	tuple->data = new void*[size];
	memset(tuple->data, 0, size * sizeof(void*));
	for (i = 0; i < size; i++) {
		void * obj = unmarshal_load(m);
		if (!obj) {
			delete tuple;
			return NULL;
		}
		tuple->data[i] = obj;
	}
	return tuple;
}

void * false_fn(unmarshal_bytes * m) {
	return &un_false;
}

void * true_fn(unmarshal_bytes * m) {
	return &un_true;
}

void init_unmarshal() {
	unmarshal_map['0'] = null_fn;
	unmarshal_map['('] = tuple_fn;
	unmarshal_map['N'] = none_fn;
	unmarshal_map['I'] = longint_fn;
	unmarshal_map['g'] = binfloat_fn;
	unmarshal_map['.'];
	unmarshal_map['t'] = intstr_fn;
	unmarshal_map['s'] = str_fn;
	unmarshal_map['F'] = false_fn;
	unmarshal_map['T'] = true_fn;
	unmarshal_map['i'] = int_fn;
	unmarshal_map['l'] = long_fn;
	unmarshal_map['R'] = stringref_fn;
	unmarshal_map['S'] = stop_iteration_fn;
	unmarshal_map['y'] = bin_complex_fn;

	unmarshal_map['u'] = unicode_fn;
	unmarshal_map['c'] = code_fn;
}

/*
unmarshal_map = {
	"0": "C_NULL",
	"N" : "None",
	"S" : "stopIteration",
	"." : "Ellipsis",
	"F" : "False",
	"T" : "True",
	"i" : "int32",
	"l" : "long",
	"I" : "int64",
	"f" : "float",
	"g" : "binary_float",
	"x" : "complex",
	"y" : "binary_complex",
	"s" : "string",
	"A" : "ASCII_interned",
	"a" : "ASCII",
	"z" : "short_ASCII",
	"Z" : "short_ASCII_interned",
	"t" : "interned",
	"u" : "unicode",
	")" : "small_tuple",
	"(" : "tuple",
	"[" : "list",
	"<" : "frozenset",
	">" : "set",
	"{" : "dict",
	"R" : "python2_string_reference",
	"c" : "code",
	"C" : "code",
	"r": "object_reference",
	"?" : "unknown",
}
*/

int unmarshal_from_bytes(byte * data, int sz, un_type ** out) {
	unmarshal_bytes b = { 0, };
	b.current = b.st = data;
	b.lim = data + sz;

	void * rt = unmarshal_load(&b);
	if (!rt) {
		printf("marshal error\n");
		return -1;
	}
	*out = (un_type*)rt;
	return 0;
}

un_complex * un_coerce_complex(void * arg) {
	un_complex * c = (un_complex*)arg;
	py_assert(c->type.type == TYPE_BINARY_COMPLEX, "Py coercion failed (tuple)");
	return c;
}

un_tuple * un_coerce_tuple(void * arg) {
	un_tuple * tuple = (un_tuple*)arg;
	py_assert(tuple->type.type == TYPE_TUPLE,"Py coercion failed (tuple)");
	return tuple;
}

un_unicode * un_coerce_unicode(void * arg) {
	un_unicode * un = (un_unicode*)arg;
	py_assert(un->type.type == TYPE_UNICODE, "Py coercion failed (unicode)");
	return un;
}

un_str * un_coerce_str(void * arg) {
	un_str * str = (un_str*)arg;
	py_assert(str->type.type == TYPE_STRING, "Py coercion failed (string, was %c)",str->type.type);
	return str;
}

un_str * un_resolve_strref(void * arg) {
	un_stringref * str = (un_stringref*)arg;
	py_assert(str->type.type == TYPE_STRINGREF, "Py coercion failed (stringref)");
	return str->ref;
}

un_code * un_coerce_code(void * arg) {
	un_code * cc = (un_code*)arg;
	py_assert(cc->type.type == TYPE_CODE, "Py coercion failed (code)");
	return cc;
}

un_double * un_coerce_double(void * arg) {
	un_double * cc = (un_double*)arg;
	py_assert(cc->type.type == TYPE_FLOAT, "Py coercion failed (float)");
	return cc;
}

char * un_resolve_str(void * arg) {
	un_str * str = (un_str*)arg;
	
	if (str->type.type == TYPE_STRINGREF) {
		return un_resolve_strref(arg)->str;
	}
	py_assert(str->type.type == TYPE_STRING, "Py resolve failed (was %c)", str->type.type);
	
	return str->str;
}

un_str * un_reduce_str(void * arg) {
	un_str * str = (un_str*)arg;
	if (str->type.type == TYPE_STRINGREF) {
		return un_resolve_strref(arg);
	}
	py_assert(str->type.type == TYPE_STRING, "Py resolve failed (was %c)", str->type.type);
	return str;
}

char * un_print_tuple(char * out, void * arg) {
	un_tuple * t = (un_tuple*)arg;
	py_assert(t->type.type == TYPE_TUPLE, "Invalid tuple on print tuple");
	char * tt = out;
	strcpy(tt, "(");
	tt += strlen(tt);
	int i;
	for (i = 0; i < t->size; i++) {
		un_to_printable(tt, t->data[i]);
		tt += strlen(tt);
		if (i < t->size - 1) {
			strcpy(tt, ",");
			tt += strlen(tt);
		}
	}
	strcpy(tt, ")");
	return out;
	
	
}

char * un_to_printable(char * out, void * arg) {
	un_type * t = (un_type *)arg;
	switch (t->type) {
	case TYPE_LONG:
		sprintf(out, "%i", ((un_long*)t)->val);
		break;
	case TYPE_STRING:
	case TYPE_STRINGREF:
		sprintf(out, "%s", un_resolve_str(arg));
		break;
	case TYPE_TUPLE:
		un_print_tuple(out, arg);
		break;
	case TYPE_NONE:
		strcpy(out, "None");
		break;
	case TYPE_UNICODE: {
		un_unicode * un = (un_unicode*)arg;
		strcpy(out, un->original_bytes);
		break;
	}
	default:
		py_assert(0, "un not printable %c",t->type);
	}
	return out;
}


/*
 * Debug stuff
 */

char * un_dump_object(char * out, void * arg) {
	char tmp[1024];
	out[0] = 0;
	if (!arg) {
		sprintf(out,"(null)");
		return out;
	}
	un_type * t = (un_type *)arg;
	
	switch (t->type) {
	case TYPE_UNICODE: {
		un_unicode * u = (un_unicode*)t;
		
		sprintf(out, "unicode: %s", u->original_bytes);
		break;
	}
		
	case TYPE_FLOAT:
		sprintf(out, "float: %lf", ((un_double*)t)->val);
		break;
	case TYPE_LONG:
		sprintf(out, "long: %i", ((un_long*)t)->val);
		break;
	case TYPE_STRING:
	case TYPE_STRINGREF:
		snprintf(out, 512, "str: %s", un_resolve_str(arg));
		break;	
	case TYPE_TUPLE: {
		un_tuple * tuple = (un_tuple*)arg;
		char * t = out;
		t[0] = '(';
		t++;
		int i;
		for (i = 0; i < tuple->size; i++) {
			un_dump_object(tmp, tuple->data[i]);
			sprintf(t, "%s,",tmp);
			t += strlen(t);
		}
		t[0] = ')';
		t[1] = 0;
		break;
	}
	default:
		sprintf(out, "obj: %c", t->type);
	}

	return out;
	
}

void un_dump_code(un_code * c) {
	printf("Code argcount: %i; nlocals: %i; stacksize %i; flags: %X \n", c->argcount, c->nlocals, c->stacksize, c->flags);
	printf("name: %s\n", un_resolve_str(c->name));
	printf("filename: %s\n", un_resolve_str(c->filename));
	printf("first line: %i\n", c->firstlineno);
	printf("code object: %c\n", ((un_type*)c->code)->type);
	printf("Consts:\n");
	char tmp[1024];
	int i;
	for (i = 0; i < c->consts->size; i++) {
		un_dump_object(tmp,c->consts->data[i]);
		printf("%s\n", tmp);
	}
	
	printf("Names:\n");
	for (i = 0; i < c->names->size; i++) {
		un_dump_object(tmp, c->names->data[i]);
		printf("%s\n", tmp);
	}
	printf("Varnames:\n");
	for (i = 0; i < c->varnames->size; i++) {
		un_dump_object(tmp, c->varnames->data[i]);
		printf("%s\n", tmp);
	}
	printf("Freevars:\n");
	for (i = 0; i < c->freevars->size; i++) {
		un_dump_object(tmp, c->freevars->data[i]);
		printf("%s\n", tmp);
	}
	printf("Cellvars: %i\n",((un_tuple *)c->cellvars)->size);

}



int un_str_size(void * arg) {
	un_str * str = (un_str*)arg;
	if (str->type.type == TYPE_STRINGREF) {
		un_stringref * ref = (un_stringref *)arg;
		return ref->ref->size;
	}
	return str->size;
}

int64 un_resolve_int(void * arg) {
	un_type * typ = (un_type*)arg;
	if (typ->type == TYPE_LONG) {
		un_long * l = (un_long *) arg;
		return l->val*l->sign;
	}
	if (typ->type == TYPE_INT64) {
		un_longlong * l = (un_longlong *)arg;
		return l->val;
	}
	py_assert(0,"Unknown un resolve %c\n",typ->type);
	return 0;	
}
