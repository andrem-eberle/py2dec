#pragma once
#include "common.h"
#include "flow.h"
#include "disasm.h"
#include "unmarshal.h"
#include "source-util.h"

void gen_source(py_function * root, source_gen_out_buf* out);
void init_gen_print();
