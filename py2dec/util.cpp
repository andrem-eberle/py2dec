#include "common.h"
#include <stdarg.h>

void py_assert1(char * file, int line, int val, char * msg, ...) {
	
	if (!val) {
		va_list va;
		va_start(va, msg);
		char out[1024];
		vsprintf(out, msg, va);
		printf("%s (%i) ERROR: %s\n", file,line,out);
		exit(1);
	}
}

int num_len(uint32 val) {
	if (val == 0) return 1;
	int len = 0;
	while (val) {
		len++;
		val /= 10;
	}
	return len;
}

char * right_sprint_num(char * out, int val, int max_len) {
	int line_len = num_len(val);
	int i;
	char * t = out;
	for (i = 0; i < max_len - line_len; i++) {
		*t++ = ' ';
	}
	sprintf(t, "%i", val);
	t += strlen(t);
	return t;
}

void timequery_start(uint64 * st) {
#ifdef _WIN32
	QueryPerformanceCounter((LARGE_INTEGER*)st);
#endif
}

void timequery_end(uint64 st) {
#ifdef _WIN32
	LARGE_INTEGER qend, qcount;	
	QueryPerformanceCounter(&qend);
	QueryPerformanceFrequency(&qcount);
	double dtime = qend.QuadPart - st;
	double dc = qcount.QuadPart;
	printf("Reachability total time: %llu counts -- %lf\n microseconds", qend.QuadPart - st, dtime / dc);
#endif
}