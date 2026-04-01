#include "flow.h"
#include "common.h"
#include "earray.h"
#include "opcodes.h"
#include "log.h"

#ifdef LOG_STACK_SOLVER
#define pylog(...) pylog_type("stack-solver",__VA_ARGS__)
#endif

void solve_node(flow_node * n, py_function * f);

enum stack_entry_type {
	STACK_ENTRY_TYPE_REGULAR,
	STACK_ENTRY_TYPE_EXCEPTION
};

typedef struct ss_stack_entry {
	py_instruction * inserter;
	int type;
	ss_stack_entry() {
		memset(this, 0, sizeof(ss_stack_entry));
		type = STACK_ENTRY_TYPE_REGULAR;
	}

	ss_stack_entry(int itype) {
		memset(this, 0, sizeof(ss_stack_entry));
		type = itype;
	}
} ss_stack_entry;

typedef struct ss_stack_info {
	ss_stack_entry * s_data;
	int ssp;
} ss_stack_info;

static py_instruction except_placeholder;

void init_solver() {
	except_placeholder.opcode = EXCEPT_PLACEHOLDER;
	strcpy(except_placeholder.highlevel_name, "EXCEPT_PLACEHOLDER");
}

void flow_set_flags(earray * flow_graph) {
	int i;
	
	for (i = 0; i < flow_graph->size; i++) {
		flow_node * n = earray_get(flow_graph, i, flow_node*);
		py_instruction * inst = n->initial_inst;
		py_assert(inst != NULL, "bad node on graph flow");
		
		while (inst->off < n->end_off) {			
			if (inst->opcode == SETUP_EXCEPT) {
				int j;
				for (j = 0; j < n->outgoing.size; j++) {
					flow_edge * e = earray_get(&n->outgoing, j, flow_edge*);
					flow_node * n1 = e->node;
					if (n1->begin_off == inst->to_jmp) {
						n1->flags |= FLOW_FLAG_EXCEPTION;
						pylog("set except flag %i\n", n1->begin_off);
					}
				}
			}
			else if (inst->opcode == SETUP_FINALLY) {
				int j;
				for (j = 0; j < n->outgoing.size; j++) {
					flow_edge * e = earray_get(&n->outgoing, j, flow_edge*);
					flow_node * n1 = e->node;
					if (n1->begin_off == inst->to_jmp) {
						n1->flags |= FLOW_FLAG_FINALLY;
						pylog("set finally flag %i\n", n1->begin_off);
					}
				}
			}
			if (inst == n->final_inst) {
				break;
			}
			inst++;
		}
	}
}

int solve_backwards(flow_node * n, py_function * f, int stack_depth, py_instruction ** out, int idx, py_instruction *ref, int ignore_iter) {
	if (!n->stack_info) {
		solve_node(n, f);
	}

	ss_stack_info * st = (ss_stack_info*)n->stack_info;
	pylog("backward flags %X %i, %i %i\n", n->flags,n->begin_off,st->ssp,stack_depth);

	//JUMP_IF_FALSE_OR_POP
	if (n->final_inst->opcode == JUMP_IF_FALSE_OR_POP) {
		pylog("possible gap\n");
	}

	if (st->ssp < stack_depth) {
		int lim = st->ssp;
		if (n->flags & FLOW_FLAG_EXCEPTION) {
			int i;
			int j = st->ssp - 1;
			for (i = idx; i < lim; i++) {
				out[i] = st->s_data[j].inserter;
				st->s_data[j].inserter->reverse_stack_referrals.add(ref);
				printf("acquired from %s\n", out[i]->highlevel_name);
				j--;
			}
			for (; i < (stack_depth - st->ssp); i++) {
				// fill the remaining with exception data
				out[i] = &except_placeholder;
			}
		}
		else {
			flow_node * nback = earray_get(&n->incoming, 0, flow_node*);
			solve_backwards(nback,f,stack_depth,out,idx,ref,0);
			//py_assert(0, "stack underrun on node flow");
			
		}
	}
	else {
		int i;
		int j = st->ssp - 1;
		
		int loop_try = 0;
		int k = idx;
		pylog("st size %i\n", st->ssp);
		while( k < (idx + stack_depth) && j>=0) {
			pylog("st size %s\n", st->s_data[j].inserter->highlevel_name);
			if (st->s_data[j].inserter->opcode == FOR_ITER && (st->s_data[j].inserter->to_jmp == ref->off)) {
				// for iter in this case pops the stack, so it is not valid 
				loop_try = 1;
				j--;
				continue;
			}
			if (ignore_iter && st->s_data[j].inserter->opcode == GET_ITER) {				
				
				j--;				
				continue;
			}
			
			pylog("back solved %s %i %i\n", st->s_data[j].inserter->highlevel_name,j,stack_depth);
			out[k++] = st->s_data[j].inserter;
			st->s_data[j].inserter->reverse_stack_referrals.add(ref);
			j--;
			
		}
		pylog("Rem %i", stack_depth - k);
		if (loop_try && (stack_depth-k) > 0) {
			pylog("Attempting to get from loop backwards");
			flow_node * nback = flow_loop_get_non_looped(n);
			py_assert(nback != NULL, "Invalid back loop on FOR_ITER?");
			pylog("nback %i %i\n", nback->begin_off,n->begin_off);
			solve_backwards(nback, f, (stack_depth - k),out , k, ref,1);
			pylog("Got %s\n", out[k]->highlevel_name);
		}
	}

	return 0;
}

void solve_node(flow_node * n, py_function * f) {
	py_instruction * inst = n->initial_inst;
	py_assert(inst != NULL, "bad node on graph flow");
	ss_stack_info * st = new ss_stack_info();
	n->stack_info = st;
	st->s_data = new ss_stack_entry[f->code->stacksize+1];
	st->ssp = 0;
	if (n->flags & FLOW_FLAG_EXCEPTION) {
		int i;
		for (i = 0; i < 3; i++) {
			py_assert(i < f->code->stacksize + 1, "Stack overrun");
			st->s_data[i].inserter = &except_placeholder;
		}
		st->ssp = 3;
	}
	pylog("flags %X\n", n->flags);
	pylog("solving for  node %i - start %X %i %i, %llX\n", n->begin_off,n->flags,n->final_inst->off,n->end_off,n);
	while (inst <= n->final_inst) {
		py_assert(st->ssp >= 0, "Bad stack pointer on stack solver %i",st->ssp);
		pylog("%s %i ssp: %i %i, out: %i, put %i, peek %i\n", inst->highlevel_name, inst->off, st->ssp,inst->arg,inst->tos_op_out,inst->tos_op_in,inst->tos_op_peek);

		if (inst->tos_op_out > 0) {
			inst->stack_referrals = new py_instruction*[inst->tos_op_out];
			memset(inst->stack_referrals, 0, inst->tos_op_out * sizeof(void*));

			inst->stack_referrals_sz = inst->tos_op_out;
			int toconsume = inst->tos_op_out - inst->tos_op_peek;
			if (st->ssp < inst->tos_op_out) {
				pylog("back solve %i %i\n", st->ssp, inst->tos_op_out);
				int i, k = 0;
				pylog("n flags %X %i %i\n", n->flags,n->begin_off,n->incoming.size);
				for (i = st->ssp - 1; i >= 0; i--) {
					py_assert(k < inst->tos_op_out, "Stack overrun");
					inst->stack_referrals[k++] = st->s_data[i].inserter;

					st->s_data[i].inserter->reverse_stack_referrals.add(inst);
				}
				if (n->flags & FLOW_FLAG_EXCEPTION) {					
					for (i = inst->tos_op_out - 1; i >= st->ssp; i--) {		
						py_assert(k < inst->tos_op_out, "Stack overrun");
						inst->stack_referrals[k++] = &except_placeholder;
					}
				}
				else if (n->incoming.size == 1) {
					flow_node * prev = earray_get(&n->incoming, 0, flow_node*);
					pylog("using incoming %i\n", prev->initial_inst->off);
					solve_backwards(prev, f, inst->tos_op_out - st->ssp, inst->stack_referrals,k,inst,0);
					
				}				
				else {
					int ncount = 0;
					int i,j;
					flow_node * result = NULL;
					for (i = 0; i < n->incoming.size; i++) {
						flow_node * inc = earray_get(&n->incoming, i, flow_node*);
						for (j = 0; j < inc->outgoing.size; j++) {
							flow_edge * e = earray_get(&inc->outgoing, j, flow_edge*);
							flow_node * nref = e->node;
							if (nref == n && !(e->flags & FLOW_EDGE_FLAG_LOOP)) {
								if (inc->final_inst->opcode != JUMP_IF_FALSE_OR_POP) {

									ncount++;
									result = inc;
								}
							}
							
							if (nref == n) {
								break;
							}
						}
					}
					if (ncount != 1) {
						flow_node * prev = earray_get(&n->incoming, 0, flow_node*);
						pylog("using incoming %i\n", prev->initial_inst->off);
						solve_backwards(prev, f, inst->tos_op_out - st->ssp, inst->stack_referrals, k, inst, 0);
						//py_assert(0, "stack underrun 2 on node flow %i\n", n->incoming.size);
					}
					else {
						pylog("incoming solved as loops are discarded, using %i\n", result->initial_inst->off);
						solve_backwards(result, f, inst->tos_op_out - st->ssp, inst->stack_referrals, k, inst, 0);
					}
					
					
				}
				py_assert(k <= inst->tos_op_out, "Overrun on stack inst referrals");
				
			}
			else {
				int i,k=0;
				for (i = st->ssp - 1; i >= (st->ssp - inst->tos_op_out); i--) {
					py_assert(k < inst->tos_op_out, "Stack overrun");
					inst->stack_referrals[k++] = st->s_data[i].inserter;
					st->s_data[i].inserter->reverse_stack_referrals.add(inst);
				}
				py_assert(k <= inst->tos_op_out, "Overrun on stack inst referrals");
			}
			
			int j;
			for (j = 0; j < inst->stack_referrals_sz; j++) {
				py_assert(inst->stack_referrals[j] != NULL, "Invalid stack referral on stack solver");
			}

			if (toconsume) {
				st->ssp -= inst->tos_op_out;
				if (st->ssp < 0) {
					st->ssp = 0;
				}
			}
		}
		if (inst->tos_op_in > 0) {
			int i;
			for (i = 0; i < inst->tos_op_in; i++) {
				py_assert(st->ssp < f->code->stacksize + 1, "Stack overrun %i %i",st->ssp, f->code->stacksize + 1);
				st->s_data[st->ssp].inserter = inst;
				st->ssp++;
			}
		}
		inst++;
	}

	
	
	pylog("Node solver finished for %i with remaining stack: %i\n",n->begin_off, st->ssp);
	
}

void top_down_solver(earray * flow_graph, py_function * f) {

	pylog("top_down_solver starting for %s", f->name);
	flow_set_flags(flow_graph);
	int i;
	pylog("flow size %i", flow_graph->size);
	for (i = 0; i < flow_graph->size; i++) {
		flow_node * n = earray_get(flow_graph, i, flow_node*);
		py_assert(n->flags <= 3, "Bad flags");
	}
	for (i = 0; i < flow_graph->size; i++) {
		flow_node * n = earray_get(flow_graph, i, flow_node*);
		pylog("flnode %i %i", n->begin_off, n->end_off);
		if (!n->stack_info) {
			solve_node(n, f);
		}
		
	}
	
}

#undef pylog
#define pylog(...)