#pragma once

#include "common.h"
#include <stdarg.h>

typedef struct source_gen_out_buf {
	FILE * output;
	char * buf;
	int bsize;
	int size;
	int tdepth;
	int cur_depth;
	int empty;
	int keepline;
	
	source_gen_out_buf() {
		memset(this,0,sizeof(source_gen_out_buf));
        bsize = 2048;
        buf = new char[bsize];
		empty = 1;
		keepline = 0;
	}

	void skip_line() {
		pdepth();
		int oempty = empty;
		empty = 0;
		int osize = size;
		flush();
		size = osize;
		oempty = empty;
		
	}

    void ensure(int n) {
        while (size+n >= bsize) {
            bsize *= 2;
            char * old = buf;
            buf = new char[bsize];
            memcpy(buf,old,size);
            delete[] old;
        }
    }

	void back() {
		size--;
	}

	char last() {
		return buf[size - 1];
	}

	void add_comma_if_none() {
		pdepth();
		ensure(1);
		if (buf[size - 1] != ',') {
			buf[size++] = ',';
		}
		empty = 0;
	}

    void add_space_if_none() {
		pdepth();
        ensure(1);
        if (buf[size-1] != ' ') {
            buf[size++] = ' ';			
        }
		empty = 0;
    }

	void pdepth() {
		if (!tdepth) return;
		int d = tdepth;
		tdepth = 0;
		int i;
		for (i = 0; i < d * 4; i++) {
			bprintf(" ");
		}
	}

	void set_depth(int depth) {
		tdepth = depth;
		cur_depth = depth;
	}

	void new_line(int off) {
		int depth = cur_depth;
		empty = 0;
		flush();	
		set_depth(depth+off);
	}

	void insert_line_break() {
		int depth = tdepth;
		empty = 0;
		flush();
		tdepth = depth;
	}

	void backindent() {
		tdepth--;
	}

	void remove_spaces() {
		while (buf[size - 1] == ' ') size--;
	}

	void bprintf(char * data,...) {
		pdepth();
        va_list va;
		
		va_start(va, data);
        int done = 0;
        while (!done) {
            int left = bsize-size;
            int rt = vsnprintf(buf+size,left,data,va);
            if (rt > left) {
                bsize *= 2;
                char * old = buf;
                buf = new char[bsize];
                memcpy(buf,old,size);
                delete[] old;
            }
            else {
                size += rt;
				empty = 0;
                done = 1;
            }
        }		
	}

    void pop() {
        size--;
        if (size < 0) {
            size = 0;
        }
    }

    void flush() {
		if (empty) return;
        bprintf("\n");
        fwrite(buf,1,size,output);
        size = 0;
		empty = 1;
    }
} source_gen_out_buf;