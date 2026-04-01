#pragma once
#include "common.h"

typedef struct earray {
	int fsize;
	int size;
	void ** data;

	earray() {
		data = (void**)calloc(1, sizeof(void*));
		fsize = 0;
		size = 0;
	}

	void cleanup() {
		if (data) {
			delete[] data;
		}		
	}

	void add_unique(void * elem) {
		int i;
		for (i = 0; i < size; i++) {
			if (data[i] == elem) {
				return;
			}
		}
		add(elem);
	}

	void add(void * elem) {
		if (fsize == 0) {
			fsize = 1;
			data = new void*[1];
		}
		else {
			if (size == fsize) {
				void ** old = data;
				fsize *= 2;
				data = new void*[fsize];
				memcpy(data, old, size * sizeof(void*));
				delete[] old;
			}
		}
		data[size++] = elem;
	}

	void ensure(int size) {
		
		if (size > fsize) {
			if (fsize == 0)	fsize = 1;
			while (size > fsize) fsize *= 2;
			
			void ** old = data;
			data = new void*[fsize];
			if (old) {
				memcpy(data, old, size * sizeof(void*));
				delete[] old;
			}
			
		}
	}

	void clear() {
		size = 0;
	}

	void copy(earray * src) {
		
		ensure(src->size);
		
		memcpy(data, src->data, src->size * sizeof(void*));
		size = src->size;
	}

	void * replace(int i, void * item) {
		void * t = data[i];
		data[i] = item;
		return t;
	}
} earray;

//py_assert(i<(a)->size,"Bad array access");
#define earray_get(a,i,t) ((t)(a)->data[i])
