#pragma once
#include "py_gen.h"
int instructions_same_tryblock(py_function * f, int off1, int off2);
int translate(py_function * f, py_function * out);
