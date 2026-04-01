#pragma once
#include "earray.h"
#include "py_gen.h"
#include "common.h"

void init_solver();
void top_down_solver(earray * flow_graph, py_function * f);

void init_solver2();
void solve_node2(flow_node * n, py_function * f);
void top_down_solver2(py_function * f);