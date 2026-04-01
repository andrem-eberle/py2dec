#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include "common.h"
#ifdef __linux__
#include <sys/time.h>

uint32 get_time_millis() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_usec / 1000;
}
#elif _WIN32

uint32 get_time_millis() {
	SYSTEMTIME tm;
	GetSystemTime(&tm);
	return tm.wMilliseconds;
}

#endif

static FILE * loglp = NULL;

void pylog_type(char * type, char * fmt, ...) {
	if (!loglp) {
		loglp = fopen("py2dec.log", "wb");
	}
	va_list va;
	va_start(va, fmt);
	char tmp[8192];
	char tmp2[8192];
	char ttime[32];
	vsprintf(tmp, fmt, va);
	int len = strlen(tmp);
	if (tmp[len - 1] != '\n') {
		tmp[len++] = '\n';
		tmp[len] = 0;
	}

	time_t now;
	struct tm * time_info;
	
	time(&now);
	time_info = localtime(&now);

	strftime(ttime, 32, "%H:%M:%S", time_info);

	sprintf(tmp2, "%s.%03u [%s] %s", ttime,get_time_millis(), type, tmp);
	
	fwrite(tmp2, 1, strlen(tmp2), loglp);
	
	fflush(loglp);
	va_end(va);
}