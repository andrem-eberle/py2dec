#pragma once

#include "common.h"

typedef struct g_config {
	char *filename;
	int output_asm;
	char output_asm_file[1024];
	char output_file[1024];
	g_config() {
		filename = NULL;
		output_asm = 0;
	}
} g_config;

extern g_config global_config;