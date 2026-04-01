#include "flow.h"
#include "common.h"
#include "earray.h"
#include "opcodes.h"
#include "log.h"

#ifdef LOG_STACK_SOLVER
#define pylog(...) pylog_type("stack-solver2",__VA_ARGS__)
#endif

int is_njmp(flow_node * n1, flow_node * n2);
void solve_node2(flow_node * n, py_function * f);

typedef struct ss2_stack_entry {
	py_instruction * inserter;
	int type;
	ss2_stack_entry() {
		memset(this, 0, sizeof(ss2_stack_entry));		
	}

	ss2_stack_entry(int itype) {
		memset(this, 0, sizeof(ss2_stack_entry));
		type = itype;
	}

} ss2_stack_entry;



typedef struct ss2_stack_info {
	ss2_stack_entry * s_data;
	int ssp;
	int bp;
	flow_node * origin;
	ss2_stack_info() {
		memset(this, 0, sizeof(ss2_stack_info));
	}
} ss2_stack_info;

typedef struct ss2_stack_response {
	ss2_stack_entry * resp[1024];
	int size;
} ss2_stack_response;

typedef struct ss2_node_data {
	flow_node * node;
	int bp;
	int * bps;
} ss2_node_data;

typedef struct ss2_last_get_case {
	flow_node * target;
	int bp;

} ss2_last_get_case;

typedef struct ss2_stack_collection {
	ss2_stack_info * stacks;
	int stacks_num;
	ss2_stack_info mainline;
	int bp;
	int * bps;
	int state;
	flow_node * last_node;
	flow_node * ref_node;
	int ssize;
	py_function * base;
	ss2_stack_collection * refs;
	int refsize;
	int initialized;
	int opcase;


	void clone(ss2_stack_collection * s1) {
		
		pylog("clone from %i", ref_node->begin_off);
		s1->ssize = ssize;
		s1->ref_node = ref_node;
		s1->mainline = mainline;
		s1->base = base;
		py_assert(ref_node != NULL, "Invalid node on stack collection");
		
		s1->last_node = last_node;		
		
		s1->mainline.bp = mainline.bp;
		s1->mainline.ssp = mainline.ssp;
		
		s1->initialized = 1;
		if (refsize > 0) {
			s1->refs = new ss2_stack_collection[refsize];			
			s1->refsize = refsize;
			
			int i;
			for (i = 0; i < refsize; i++) {				
	
				s1->refs[i].ref_node = refs[i].ref_node;
				s1->refs[i].initialized = 0;
				if (refs[i].initialized) {
					pylog("cloning eagerly from %i",refs[i].ref_node->begin_off);
					refs[i].clone(&s1->refs[i]);
					s1->refs[i].initialized = 1;
					pylog("%llX %llX %i %llX %i", s1, &s1->refs[i],s1->refs[i].opcase,&refs[i],refs[i].opcase);
					s1->refs[i].opcase = refs[i].opcase;
				}
				
				py_assert(refs[i].ref_node != NULL, "Invalid ref node on stack solver");
			}
		}	

		py_instruction * last = s1->ref_node->final_inst;
		if (last->opcode == JUMP_IF_FALSE_OR_POP ||
			last->opcode == JUMP_IF_TRUE_OR_POP) {
			s1->opcase = 1;
		}
		
		
	}

	ss2_stack_collection() {
		memset(this, 0, sizeof(ss2_stack_collection));
	}

	ss2_stack_collection(int size, flow_node * n, py_function * f) {
		refs = NULL;
		ssize = size;
		mainline.s_data = new ss2_stack_entry[size];
		refsize = 0;
		stacks_num = 0;
		bp = 0;
		state = 0;
		last_node = n;
		bps = NULL;
		ref_node = n;
		base = f;
		initialized = 1;
		opcase = 0;
	}

	int get(ss2_stack_response * r, int peek, flow_node * origin) {
		int i;
		
		pylog("get called, ssp %i stacks_num %i bp %i, local node: %i, opcase %i, this %llX", mainline.ssp,stacks_num,bp,ref_node->begin_off,opcase,this);

		if (opcase && origin != ref_node) {
			int njmp = is_njmp(ref_node, origin);
			py_instruction * last = ref_node->final_inst;
			pylog("conditional pop case %i %llX", njmp,last);
			if (!njmp) {
				r->resp[0] = new ss2_stack_entry();
				py_assert(last->stackbacks_sz == 0, "Multiple referrals on JUMP_OR_POP?");
				r->resp[0]->inserter = last->stack_referrals[0];
				pylog("got from op case %i %s", r->resp[0]->inserter->off, r->resp[0]->inserter->highlevel_name);
				opcase = 0;
				return 1;
			}
		}
		
		
		if (mainline.ssp > 0) {
			pylog("getting from mainline %i %s", 
				mainline.s_data[mainline.ssp - 1].inserter->off, mainline.s_data[mainline.ssp - 1].inserter->highlevel_name);
			r->resp[0] = &mainline.s_data[mainline.ssp-1];
			if (!peek) {
				mainline.ssp--;
			}
			return 1;
		}

		if (stacks_num > 0) {			
			for (i = 0; i < stacks_num; i++) {
				py_assert(stacks[i].ssp > 0, "Solver went too deep into multi stack");
				r->resp[i] = &stacks[i].s_data[stacks[i].ssp-1];
				if (!peek) {
					stacks[i].ssp--;
				}
			}
			return stacks_num;
		}
		if (refs) {
			pylog("inserting from our refs %i, node ref is %i",refsize,ref_node->begin_off);
			for (i = 0;i < refsize; i++) {
				pylog("ref state %i %llX", refs[i].initialized, &refs[i]);
				py_assert(refs[i].ref_node != NULL, "Invalid stack ref on solver");
				if (!refs[i].initialized) {
					ss2_stack_collection * ssx = (ss2_stack_collection*)refs[i].ref_node->stack_info;
					pylog("cloning stack ref from %i", refs[i].ref_node->begin_off);
					ssx->clone(&refs[i]);
				}
				py_assert(refs[i].ref_node != ref_node, "Invalid refnode loop on stack");
				
				pylog("ref %i %i", refs[i].ref_node->begin_off, refs[i].bp);
				
				ss2_stack_collection * ssx = &refs[i];
				ss2_stack_response tmp;
				pylog("ref stack base: %llX", ssx);
				

				int rrt = ssx->get(&tmp, 0,ref_node);
				py_assert(rrt == 1, "Solver went too deep into multi stack");
				r->resp[i] = tmp.resp[0];

				
				
				pylog("from refs %i %s", r->resp[i]->inserter->off, r->resp[i]->inserter->highlevel_name);
				
			}
			
			return refsize;
		}		

		flow_node * ref = last_node;
		pylog("incoming size %i", last_node->incoming.size);
			
		pylog("get from several back nodes %i", last_node->incoming.size);
		refs = new ss2_stack_collection[last_node->incoming.size];
		
		int k = 0;
		int ix = 0;
		for (i = 0; i < last_node->incoming.size; i++) {
			flow_node * n = earray_get(&last_node->incoming, i, flow_node *);
			
			if (flow_is_loop(n, last_node)) {
				continue;
			}
			solve_node2(n,base);
			ss2_stack_collection * ssx = (ss2_stack_collection*)n->stack_info;
			
			ssx->clone(&refs[ix++]);

			//refs[i].target = n;
			pylog("back node %i %i %i\n", n->begin_off,n->incoming.size,ssx->mainline.ssp);

			ss2_stack_response tmp;
			int j;
			pylog("ix %i", i);
			pylog("asking instruction from back node, ref: %llX",&refs[ix-1]);
			int rrt = refs[ix-1].get(&tmp, 0, ref_node);
			pylog("retrieving from back node yielded %i", rrt);
			for (j = 0; j < rrt; j++) {
				r->resp[k++] = tmp.resp[j];
				pylog("got %i %s", tmp.resp[j]->inserter->off, tmp.resp[j]->inserter->highlevel_name);
			}	
			
		}
		refsize = ix;
		pylog("stacks_num %i refs %i", stacks_num,refsize);
		
		return k;
			
		
	}

	void shift() {
		if (mainline.ssp == 0) {
			mainline.ssp = 1;
			return;
		}
		int i;
		for (i = mainline.ssp; i > 0; i--) {
			mainline.s_data[i] = mainline.s_data[i - 1];
		}
		
		mainline.ssp++;
	}

	void shift_stacks() {
		py_assert(stacks_num > 0, "Invalid stack shift");
		int j, i;
		for (j = 0; j < stacks_num; j++) {
			for (i = stacks[j].ssp; i > 0; i--) {
				stacks[j].s_data[i] = stacks[j].s_data[i - 1];
			}
			stacks[j].ssp++;
		}
	}

	void fetch(int n) {
		int i;
		pylog("fetching %i -- ssp: %i", n, mainline.ssp);
		py_assert(n <= 4, "Invalid fetch on stack");
		if (mainline.ssp >= n) {
			pylog("enough elements in mainline already");
			return;
		}
		
		ss2_stack_response rr[4];
		ss2_stack_entry rre[4];
		for (i = 0; i < n; i++) {
			pylog("fetch ask for node");
			int rt = get(&rr[i], 0, ref_node);
			rr[i].size = rt;
			rre[i] = *rr[i].resp[0];
		}

		for (i = n-1; i >=0; i--) {
			int rt = rr[i].size;
		
			if (rt == 1 && stacks_num == 0) {
				shift();
				mainline.s_data[0] = rre[n - (i + 1)];
				
				pylog("fetch inserting in mainline %i, %i %s %i", mainline.ssp,
					rre[n-(i+1)].inserter->off, rre[n - (i + 1)].inserter->highlevel_name,i);
			}
			else {
				int j;
				pylog("fetch inserting in multi stacks %i stacks_num %i, case %i", rt,stacks_num,i);
				if (stacks_num == 0) {
					stacks = new ss2_stack_info[rt];
					stacks_num = rt;
					for (j = 0; j < stacks_num; j++) {
						stacks[j].s_data = new ss2_stack_entry[ssize];
					}					
				}
				else {
					shift_stacks();
				}				
				
				for (j = 0; j < stacks_num; j++) {
					if (rt == 1) {
						stacks[j].s_data[0] = *rr[i].resp[0];						
					}
					else {
						py_assert(rt == stacks_num, "Invalid stack insert");
						stacks[j].s_data[0] = *rr[i].resp[j];
						
						pylog("insert %i", rr[i].resp[j]->inserter->off);
					}
					if (stacks[j].ssp == 0) {
						stacks[j].ssp++;
					}
					pylog("stacks size %i", stacks[j].ssp);
				}
			}
		}
		
	}

	void flip(int n) {
		ss2_stack_entry tmp;
		int i,j;
		
		if (mainline.ssp >= n) {
			
			tmp = mainline.s_data[mainline.ssp - 1];
			pylog("flip mainline %i %i %i %s", n,mainline.ssp,tmp.inserter->off,tmp.inserter->highlevel_name);
			for (i = mainline.ssp - 1; i > (mainline.ssp-n); i--) {
				mainline.s_data[i] = mainline.s_data[i - 1];				
			}
			mainline.s_data[mainline.ssp - n] = tmp;
		}
		else  {
			pylog("flip multistack %i %i", mainline.ssp,n);
			int tomove = mainline.ssp;
			int toshift = n - tomove;
			if (tomove > 0) {
				tmp = mainline.s_data[mainline.ssp - 1];
			}
			
			py_assert(stacks_num > 0, "Invalid flip on bad stack");
			for (i = 0; i < stacks_num; i++) {
				if (tomove == 0) {
					tmp = stacks[i].s_data[stacks[i].ssp-1];
					pylog("tomove %i %s %i %i", tmp.inserter->off,tmp.inserter->highlevel_name,toshift, stacks[i].ssp);
				}
				for (j = stacks[i].ssp - 1; j > stacks[i].ssp - toshift; j--) {
					stacks[i].s_data[j] = stacks[i].s_data[j - 1];
					int l;
					for (l = 0; l < tomove-1; l++) {						
						stacks[i].s_data[stacks[i].ssp + toshift+l] = mainline.s_data[l];
					}
				}
				stacks[i].s_data[stacks[i].ssp - toshift] = tmp;
				
				stacks[i].ssp+= tomove;
			}
			mainline.ssp = 0;
		}
		
	}

} ss2_stack_collection;

int is_njmp(flow_node * n1, flow_node * n2) {
	return n2->initial_inst == (n1->final_inst + 1);
}

void flow_set_flags(earray * flow_graph);
static py_instruction except_placeholder;

void init_solver2() {
	except_placeholder.opcode = EXCEPT_PLACEHOLDER;
	except_placeholder.off = -1;
	strcpy(except_placeholder.highlevel_name, "EXCEPT_PLACEHOLDER");
}

void solve_node2(flow_node * n, py_function * f) {
	if (n->stack_info) {
		return;
	}
	pylog("Solving node at %s -- %i", f->name,n->begin_off);
	ss2_stack_response rr;
	ss2_stack_collection * stackbase = new ss2_stack_collection(f->code->stacksize + 1,n,f);
	n->stack_info = stackbase;
	ss2_stack_info * stack = &stackbase->mainline;
	py_instruction * inst = n->initial_inst;

	if (n->flags & FLOW_FLAG_EXCEPTION) {
		int i;
		pylog("inserting except placeholder");
		for (i = 0; i < 3; i++) {
			py_assert(i < f->code->stacksize + 1, "Stack overrun");
			stack->s_data[i].inserter = &except_placeholder;
		}
		stack->ssp = 3;
	}

	while (inst <= n->final_inst) {
		py_assert(stack->ssp >= 0, "Bad stack pointer on stack solver %i", stack->ssp);		
		int i;
		
		pylog("inst %i %s, ssp: %i, in: %i, out: %i, -- fun %s -- ", inst->off,inst->highlevel_name,stackbase->mainline.ssp,inst->tos_op_in,inst->tos_op_out,f->name);

		if (inst->opcode == ROT_TWO) {
			stackbase->fetch(2);
			stackbase->flip(2);
		}
		else if (inst->opcode == ROT_THREE) {				
			stackbase->fetch(3);
			stackbase->flip(3);			
		}
		else if (inst->opcode == ROT_FOUR) {
			stackbase->fetch(4);
			stackbase->flip(4);
		}
		else if (inst->tos_op_out > 0) {	

			inst->stack_referrals = new py_instruction*[inst->tos_op_out];
			inst->stack_referrals_sz = inst->tos_op_out;
			int toconsume = inst->tos_op_out - inst->tos_op_peek;
			int k = 0;

			
			for (i = 0; i < inst->tos_op_out; i++) {
				
				int sz = stackbase->get(&rr,toconsume <= 0,n);
				toconsume--;
				if (sz > 1 && !inst->stackbacks_sz) {
					inst->expand_stackback(sz);
				}
				if (sz == 1 && !inst->stackbacks_sz) {
					
					//pylog("%s %i %s %i", inst->highlevel_name, inst->off, rr.resp[0]->inserter->highlevel_name, rr.resp[0]->inserter->off);
					
					inst->stack_referrals[k++] = rr.resp[0]->inserter;
					rr.resp[0]->inserter->reverse_stack_referrals.add(inst);					
				}
				else {
					int j;
					for (j = 0; j < sz; j++) {
						
						inst->stackbacks[j].stack_referrals[k] = rr.resp[j]->inserter;
						rr.resp[j]->inserter->reverse_stack_referrals.add(inst);
					}
					k++;
				}
			}		
			py_assert(k == inst->stack_referrals_sz, "Invalid stack size on instruction");
			for (i = 0; i < inst->stackbacks_sz; i++) {
				py_assert(inst->stackbacks[i].stack_referrals[0]->off >= 0, "Invalid instruction on stack solver");
			}

			pylog("instruction has %i stackbacks, %i referrals", inst->stackbacks_sz,inst->stack_referrals_sz);
			if (inst->stackbacks_sz > 0) {
				for (i = 0; i < inst->stackbacks_sz; i++) {
					
					pylog("%i %s", inst->stackbacks[i].stack_referrals[0]->off, inst->stackbacks[i].stack_referrals[0]->highlevel_name);
					py_assert(inst->stackbacks[i].stack_referrals[0]->off >= 0, "Invalid instruction on stack solver");
				}
			}

		}

		for (i = 0; i < inst->tos_op_in; i++) {
			py_assert(stackbase->mainline.ssp < f->code->stacksize + 1, "Stack overrun %i %i", stackbase->mainline.ssp, f->code->stacksize + 1);
			stackbase->mainline.s_data[stackbase->mainline.ssp++].inserter = inst;
		}
		
		
		inst->coallesce();
		pylog("coallesced to %i", inst->stackbacks_sz);
		
		inst++;
	}

	

	pylog("End solver for node at %s -- %i, ssp: %i", f->name, n->begin_off,stackbase->mainline.ssp);
}

void top_down_solver2(py_function * f) {
	pylog("Stack solver starting for %s", f->name);
	flow_graph * graph = f->flow_nodes;
	flow_set_flags(&graph->nodes);
	int i;
	for (i = 0; i < graph->nodes.size; i++) {
		flow_node * n = earray_get(&graph->nodes, i, flow_node*);
		solve_node2(n,f);
	}
	pylog("End solver for %s", f->name);

}

#undef pylog
#define pylog(...)