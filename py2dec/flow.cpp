#include "common.h"
#include "flow.h"
#include "earray.h"
#include "opcodes.h"
#include "hash.h"
#include <limits.h>

#ifdef LOG_STACK_SOLVER
#define pylog(...) pylog_type("flow",__VA_ARGS__)
#endif

static int dotcc = 1;

void todot(earray * nodes, char * name) {
	int i;
	char tmp[256];	
	sprintf(tmp, "%s-%i.dot", name,dotcc++);
	char * t = tmp;
	while (*t) {
		if (*t == '<' || *t == '>') {
			*t = '_';
		}
		t++;
	}
	FILE * fp = fopen(tmp,"wb");
	if (!fp) {
		pylog("WARNING - todot failed, file name is invalid %s", name);
		return;
	}
	fprintf(fp, "digraph {\n");

	if (nodes->size == 1) {
		flow_node * n = earray_get(nodes, 0, flow_node*);
		fprintf(fp, "\"%i - %i\"", n->begin_off, n->end_off);
	}
	
	for (i = 0; i < nodes->size; i++) {
		int j;
		flow_node * n = earray_get(nodes, i, flow_node*);
		for (j = 0; j < n->outgoing.size; j++) {
			flow_edge * e = earray_get(&n->outgoing, j, flow_edge*);
			flow_node * targ = e->node;
			if (e->flags & FLOW_EDGE_FLAG_LOOP) {
				fprintf(fp, "\"%i - %i\" -> \"%i - %i\"[color = blue]", n->begin_off, n->end_off, targ->begin_off, targ->end_off);				
			}
			else if (e->flags & FLOW_EDGE_FLAG_IMPLICIT) {
				fprintf(fp, "\"%i - %i\" -> \"%i - %i\"[color = red]", n->begin_off, n->end_off, targ->begin_off, targ->end_off);
			}
			else if (e->flags & FLOW_EDGE_FLAG_BREAK) {
				fprintf(fp, "\"%i - %i\" -> \"%i - %i\"[color = green]", n->begin_off, n->end_off, targ->begin_off, targ->end_off);
			}
			else {
				fprintf(fp, "\"%i - %i\" -> \"%i - %i\"", n->begin_off, n->end_off, targ->begin_off, targ->end_off);
			}
		}
	
	}
	fprintf(fp, "}\n");
	fclose(fp);
}

py_instruction * flow_get_inst(py_instruction * instruction_set, int instruction_set_size, int off) {
	int i;
	// FIXME slow offset to index conversion, get a hashmap here or something
	for (i = 0; i < instruction_set_size; i++) {
		py_instruction * inst = &instruction_set[i];
		if (inst->off == off) {
			return inst;
		}
	}
	return NULL;
}

flow_node * flow_loop_get_non_looped(flow_node *n) {
	int incoming = n->incoming.size;
	int i;
	for (i = 0; i < n->incoming.size; i++) {
		flow_node * n1 = earray_get(&n->incoming, i, flow_node*);
		int j;
		for (j = 0; j < n1->outgoing.size; j++) {
			flow_edge * e = earray_get(&n1->outgoing, j, flow_edge*);
			if (e->node == n) {
				if (!(e->flags & FLOW_EDGE_FLAG_LOOP)) {
					return n1;
				}
				break;
			}
		}
		py_assert(j < n1->outgoing.size, "Bad flow count");
	}
	return NULL;
}

int flow_count_non_loop_incoming(flow_node * n) {

	int incoming = n->incoming.size;
	int i;
	for (i = 0; i < n->incoming.size; i++) {
		flow_node * n1 = earray_get(&n->incoming, i, flow_node*);
		int j;
		for (j = 0; j < n1->outgoing.size; j++) {
			flow_edge * e = earray_get(&n1->outgoing, j, flow_edge*);
			if (e->node == n) {
				if (e->flags & FLOW_EDGE_FLAG_LOOP) {
					incoming--;
				}
				break;
			}
		}
		py_assert(j < n1->outgoing.size, "Bad flow count");
	}
	return incoming;
}

void flow_jmp_add(flow_node * n, py_instruction * inst, py_instruction * next, earray *visited,
	py_instruction * instruction_set, int instruction_set_size, flow_node ** nodemap, int i, flow_queue * queue, uint32 target) {
	flow_node *tmp, * n1;
	
	int j;
	int found = 0;
	for (j = 0; j < visited->size; j++) {

		flow_node * n1 = earray_get(visited, j, flow_node*);

		if (target == n1->begin_off) {
			found = 1;
			flow_edge * e = new flow_edge(n1);
			pylog("node add %i, from %i", n1->begin_off,n->begin_off);
			n->outgoing.add(e);
			n1->incoming.add(n);
			
			break;
		}
		if (target > n1->begin_off) {

			if (n1->end_off == -1 && inst->off >= target) {

				py_assert(n == n1, "Unexpected flow assertion");
				py_instruction * targ_inst = flow_get_inst(instruction_set, instruction_set_size, target);
				
				tmp = n->split(target, targ_inst - 1, targ_inst);
				visited->add(tmp);
				
				nodemap[tmp->begin_off] = tmp;

				n = tmp;

				found = 1;
				break;
			}
			else if (n1->end_off != -1 && target < n1->end_off) {				
				py_instruction * targ_inst = flow_get_inst(instruction_set, instruction_set_size, target);
				
				tmp = n1->split(target, targ_inst-1, targ_inst);

				visited->add(tmp);
				
				nodemap[tmp->begin_off] = tmp;
				n->create_edge(tmp);
				found = 1;
				break;
			}

		}
	}

	if (!found) {
		if (!nodemap[target]) {
			n1 = new flow_node();
			n1->begin_off = target;
			nodemap[target] = n1;
			
			queue->add(n1);
		}
		n1 = nodemap[target];
		flow_edge * e = new flow_edge(n1);
		n1->incoming.add(n);
		
		n->outgoing.add(e);
	}
	n->end_off = next->off;
	n->final_inst = inst;
	if (inst->jmp_conditional) {
		target = next->off;

		if (!nodemap[target]) {
			n1 = new flow_node();
			n1->begin_off = next->off;
			nodemap[target] = n1;
			
			queue->add(n1);
		}
		n1 = nodemap[target];
		n1->incoming.add(n);
		
		flow_edge * e = new flow_edge(n1);
		n->outgoing.add(e);

		
	}
	
}

int flow_get_loop(flow_node * n) {
	flow_node * n1;
	flow_node * q = n;
	flow_node * t = q;
	n->next = NULL;
	earray visited;
	while (q) {
		n1 = q;
		q = q->next;
		visited.add(n1);
		if (!q) {
			t = q;
		}
		int i;
		for (i = 0; i < n1->incoming.size; i++) {
			flow_node * qx = earray_get(&n1->incoming, i, flow_node*);
			if (qx->loop_block) {
				visited.cleanup();
				
				return qx->loop_block;
			}
			int j;
			int found = 0;
			for (j = 0; j < visited.size; j++) {
				flow_node * n2 = earray_get(&visited, j, flow_node*);
				if (n2 == qx) {
					found = 1;
					break;
				}
			}
			if (!found) {
				if (!q) {
					q = qx;
				}
				else {
					t->next = qx;
				}
				t = qx;
				qx->next = NULL;
			}
		}
	}
	py_assert(0, "Upwards loop node not found");
	return 0;
}

void flow_verify_loop(flow_node * n, int * path, int * pidx, int * visited) {
	path[*pidx] = n->idx;
	(*pidx) = (*pidx) + 1;
	visited[n->idx] = 1;
	
	int i;
	for (i = 0; i < n->outgoing.size; i++) {
		flow_edge * e = earray_get(&n->outgoing, i, flow_edge *);
		flow_node * n2 = e->node;
		int j;
		for (j = 0; j < (*pidx); j++) {
			
			if (path[j] == n2->idx) {
				//looped
				//printf("looped on %i to %i\n", n->initial_inst->off,n2->initial_inst->off);
				e->flags |= FLOW_EDGE_FLAG_LOOP;
				continue;
			}
			if (!visited[n2->idx]) {
				flow_verify_loop(n2, path, pidx, visited);
			}
		}
	}

	(*pidx) = (*pidx) - 1;
}

void flow_detect_loop(earray * nodes, py_instruction * instruction_set) {
	int i;
	int * visited = new int[nodes->size];
	int * path = new int[nodes->size];	
	memset(visited, 0, nodes->size * sizeof(int));
	
	for (i = 0; i < nodes->size; i++) {
		flow_node * n = earray_get(nodes, i, flow_node*);
		if (n->initial_inst == &instruction_set[0]) {
			int pidx = 0;
			flow_verify_loop(n, path, &pidx, visited);
			break;
		}

	}

	delete[] visited;
	delete[] path;
}

int flow_is_loop(flow_node * n1, flow_node * n2) {
	int i;
	for (i = 0; i < n1->outgoing.size; i++) {
		flow_edge * e = earray_get(&n1->outgoing, i, flow_edge*);
		if (e->node == n2) {
			if (e->flags & FLOW_EDGE_FLAG_BREAK) {
				return 4;
			}
			else if (e->flags & FLOW_EDGE_FLAG_IMPLICIT) {
				return 2;
			}
			else if (e->flags & FLOW_EDGE_FLAG_LOOP) {
				return 1;
			}
			else {
				return 0;
			}
		}
	}
	//py_assert(0, "flow_is_loop with non connected nodes");
	return -1;
}

void build_flow(py_instruction * instruction_set, int instruction_set_size, flow_graph * output, char * name) {
	pylog("Building flow for %s %llX", name,output);
	int i;
	int j;
	int lastline = -1;
	// FIXME use a hashmap or similar here
	earray * visited = &output->nodes;

	int max_offset = instruction_set[instruction_set_size - 1].off+1;
	
	flow_node ** nodemap = new flow_node*[max_offset];
	memset(nodemap, 0, max_offset * sizeof(flow_node*));
	
	flow_queue queue = flow_queue();

	flow_node * root = new flow_node();	
	
	root->begin_off = 0;
	root->end_off = -1;
	nodemap[0] = root;

	queue.add(root);
	flow_node * n1;

	while (queue.head) {		
		flow_node * n = queue.remove_first();
		pylog("Examining node %i", n->begin_off);
	
		
		visited->add(n);
		int idx = 0;
		
		for (i = 0; i < instruction_set_size; i++) {
			if (instruction_set[i].off == n->begin_off) {
				idx = i;
				break;
			}
		}
		

		n->initial_inst = &instruction_set[idx];
		py_assert(n->initial_inst != NULL, "No initial instruction on node?");

		for (i = idx; i < instruction_set_size; i++) {
			py_instruction * inst = &instruction_set[i];
			py_instruction * next = i <  instruction_set_size + 1 ?  &instruction_set[i + 1] : NULL;
			
			if (inst->loop_data) {
				n->loop_block = inst->loop_data;
			}

			if (nodemap[inst->off] && nodemap[inst->off] != n) {
				// reached another block
				
				n->end_off = inst->off;
				n->final_inst = &instruction_set[i-1];

				flow_edge * e = new flow_edge(nodemap[inst->off]);
				n->outgoing.add(e);
				nodemap[inst->off]->incoming.add(n);
				
				break;
			}
			
			if (inst->to_jmp > -1) {
				
				// reached a jmp, conditional or otherwise
				uint32 target = inst->to_jmp;
				flow_jmp_add(n, inst, next,visited,instruction_set,instruction_set_size,nodemap,i,&queue, target);
				if (inst->opcode == RETURN_VALUE) {
					// this is a 'fake' edge, included to complete the analysis model
					py_assert(n->outgoing.size == 1, "Unknown return flow construct");
					flow_edge * e = earray_get(&n->outgoing, 0, flow_edge*);
					e->flags |= FLOW_EDGE_FLAG_IMPLICIT;
				}
				if (inst->jmp_conditional == 2) {
					pylog("cond 2 %i", inst->off);
					py_assert(n->outgoing.size > 1, "Unknown return flow construct");
					flow_edge * e = earray_get(&n->outgoing, 1, flow_edge*);
					e->flags |= FLOW_EDGE_FLAG_IMPLICIT;
				}
				break;
				
			}
			else if (inst->brk) {
				
				// end of loop, search upward for the closest nested loop
				int target = flow_get_loop(n);
				flow_jmp_add(n, inst, next, visited, instruction_set, instruction_set_size, nodemap, i, &queue, target);

				flow_edge * e = earray_get(&n->outgoing, 0, flow_edge*);
				e->flags |= FLOW_EDGE_FLAG_BREAK;
				if (inst->jmp_conditional == 2) {
					pylog("cond 2 %i", inst->off);
					py_assert(n->outgoing.size > 1, "Unknown return flow construct");
					flow_edge * e = earray_get(&n->outgoing, 1, flow_edge*);
					e->flags |= FLOW_EDGE_FLAG_IMPLICIT;
				}
				break;

			}
			else if (inst->eob) {
				// end of block				
				n->end_off = inst->off + 1;
				n->final_inst = inst;
				break;
			}
			if (i == (instruction_set_size-1)) {				
				n->end_off = inst->off + 3;
				n->final_inst = inst;
				
			}

		}
		
		
	}	
	
	for (i = 0; i < visited->size; i++) {
		flow_node * n = earray_get(visited, i, flow_node*);
		n->idx = i;
	}

	flow_detect_loop(visited,instruction_set);
	
	todot(visited,name);
	
	for (j = 0; j < visited->size; j++) {
		flow_node * n1 = earray_get(visited, j, flow_node*);
		py_assert(n1->initial_inst != 0, "Bad initial inst on node");
		int k;
		
		for (i = 0; i < n1->incoming.size; i++) {
			flow_node * nx = earray_get(&n1->incoming, i, flow_node*);
		}

		py_assert(n1->begin_off == n1->initial_inst->off, "Bad instruction on flow %i != %i",n1->begin_off,n1->initial_inst->off);

		if (n1->final_inst + 1 < instruction_set + instruction_set_size) {
			py_assert(n1->end_off == (n1->final_inst + 1)->off, "Bad instruction on final flow %i != %i", n1->end_off, (n1->final_inst + 1)->off);
		}
		else {
			py_assert(n1->end_off == n1->final_inst->off+1, "Bad instruction on final flow2 %i != %i, %s", n1->end_off, n1->final_inst->off + 1,n1->final_inst->highlevel_name);
		}
		
	}

	delete[] nodemap;
	
	
}

void build_graph_reachability(flow_graph * graph) {
	graph->reachability_matrix = graph_reachability(graph->nodes.size);
	
	
	int * visited = new int[graph->nodes.size];
	int i;

	int k;
	for (k = 0; k < graph->nodes.size; k++) {
		flow_node * root = earray_get(&graph->nodes, k, flow_node*);

		flow_node * q = root;
		flow_node * t = q;
		root->next = NULL;
		memset(visited, 0, graph->nodes.size * sizeof(int));

		while (q) {
			flow_node * n = q;

			q = q->next;
			if (!q) t = q;
			
			for (i = 0; i < n->outgoing.size; i++) {
				int dist = graph->reachability_matrix.reach(root->idx, n->idx);
				flow_edge * e = earray_get(&n->outgoing, i, flow_edge*);

				if (e->flags & FLOW_EDGE_FLAG_LOOP) {
					//looped, ignore
					continue;
				}
				if (e->flags & FLOW_EDGE_FLAG_IMPLICIT) {
					// explict break of loop, we wont use it for if analysis
					continue;
				}

				flow_node * n2 = e->node;
				//printf("outgoing from %i to %i\n", n->initial_inst->off, n2->initial_inst->off);
				
				int reach;
				reach = graph->reachability_matrix.reach(root->idx, n2->idx);
				if (reach < 0) {
					//looped back into the root node, ignore
					printf("looped %i %i\n", n->initial_inst->off, n->initial_inst->off);
					continue;
				}

				//printf("dist %i %i\n", dist, reach);
				if (reach > 0) {
					dist = dist < reach ? dist+1 : reach;
				}
				else {
					dist = dist + 1;
				}
				//printf("final dist %i %X %X\n", dist,q,n2);
				graph->reachability_matrix.set_reach(root->idx, n2->idx, dist);
				graph->reachability_matrix.set_reach(n2->idx, root->idx, -dist);

				if (visited[n2->idx]) {
					continue;
				}
				
				if (!q) {
					q = n2;
				}
				else {
					t->next = n2;
				}
				n2->next = NULL;
				t = n2;

				
				visited[n2->idx] = 1;
			}
		}
	}

	delete[] visited;
	
	
}

flow_node * flow_get_node_from_offset(flow_graph * graph, int offset) {
	int i;
	// FIXME optimize this
	for(i=0;i<graph->nodes.size;i++) {
		flow_node * n = earray_get(&graph->nodes,i,flow_node*);
		
		if (offset >= n->begin_off && offset < n->end_off) {
			pylog("found at %i %i\n",offset,n->begin_off);
			return n;
		}
	}
	//py_assert(0,"Could not locate instruction in flow (%i)",offset);
	return NULL;
}

flow_node * flow_get_node_from_instruction(flow_graph * graph, py_instruction * inst) {	
	int idx = inst->off;

	return flow_get_node_from_offset(graph,idx);
			
}

flow_node * flow_closest_descendant(flow_graph * graph, flow_node * n1, flow_node * n2) {
	if (!graph->reachability_matrix.data) {
		build_graph_reachability(graph);
	}
	int lsum = INT_MAX;
	int iidx = -1;
	int i;
	py_assert(n1 != NULL && n2 != NULL, "Bad nodes on closest descendant");
	
	for (i = 0; i < graph->nodes.size; i++) {		
		if (i == n1->idx || i == n2->idx) {
			continue;
		}
		
		int r1 = graph->reachability_matrix.reach(n1->idx, i);
		int r2 = graph->reachability_matrix.reach(n2->idx, i);

		if (r1 > 0 && r2 > 0) {
			int sum = r1 + r2;
			if (sum < lsum) {
				lsum = sum;
				iidx = i;
			}
		}
	}
	
	if (iidx < 0) {
		return NULL;
	}
	flow_node * nx = earray_get(&graph->nodes, iidx, flow_node*);
	return nx;
}

void flow_left_right_reachability(flow_node * n, flow_graph * graph, flow_left_right_result * result) {
	if (!graph->reachability_matrix.data) {
		build_graph_reachability(graph);
	}
	if (n->outgoing.size != 2) {
		py_assert(0, "Reachability in invalid node (outgoing %i)",n->outgoing.size);
	}

	// 1- check if one side reaches the other
	// 2- if (1) is true, and child A -> child B check if a vertex exists which can be reached by 
	// A without going through B, and can also be reached from B
	// if (2) is true, we have an impossible if-else, in this case we need to check
	// the atoms, see if it is a chain of conditions. If not, the graph is not valid

	// if (1) or (2) are false, return the results
	memset(result, 0, sizeof(flow_left_right_result));
	
	flow_edge * e = earray_get(&n->outgoing, 0, flow_edge*);
	flow_edge * e2 = earray_get(&n->outgoing, 1, flow_edge*);
		
	flow_node * left = e->node;
	flow_node * right = e2->node;

	if (e->flags & FLOW_EDGE_FLAG_LOOP || e2->flags & FLOW_EDGE_FLAG_LOOP) {
		// case where one of the sides is a 'continue'
		result->state = STATE_NO_PATH;
		result->right = right;
		result->left = left;
		pylog("looped on child");
		result->flags |= FLOW_LR_RESULT_LOOPED;
		return;
	}

	pylog("outgoing %i %i", e->node->begin_off, e2->node->begin_off);

	int mleft = INT_MAX;
	int mright = INT_MAX;

	int i;

	pylog("reachability %i %i\n", left->initial_inst->off, right->initial_inst->off);
	int reach = graph->reachability_matrix.reach(left->idx, right->idx);
	pylog("mutual reach %i\n", reach);

	if (reach == 0) {
		// no path between nodes		
	}
	else if (reach < 0) {
		// right is ancestor of left
	}
	else if (reach > 0) {
		// left is ancestor of right
		flow_node * tmp = left;
		left = right;
		right = tmp;
	}
	pylog("right %i left %i\n", right->initial_inst->off, left->initial_inst->off);
	// find closest common descendant
	// we use distance loosely here, essentially a sum of both distances
	int lsum = INT_MAX;
	int iidx = -1;
	for (i = 0; i < graph->nodes.size; i++) {
		if (i == left->idx || i == right->idx) {
			continue;
		}
		int r1 = graph->reachability_matrix.reach(left->idx, i);
		int r2 = graph->reachability_matrix.reach(right->idx, i);
		flow_node * nn = earray_get(&graph->nodes, i, flow_node*);
		
		if (r1 > 0 && r2 > 0) {
			int sum = r1 + r2;
			if (sum < lsum) {
				lsum = sum;
				iidx = i;
			}
		}
	}
	if (iidx < 0) {
		result->right = right;
		result->left = left;
		// no common descendant
		if (reach == 0) {
			result->state = STATE_NO_PATH;
		}
		else {
			// if our descendant child here is the last node in the graph we have no desc
			result->state = STATE_PATH;
			
		}
		result->desc = NULL;
		return;
	}

	flow_node * nx = earray_get(&graph->nodes, iidx, flow_node*);
	result->desc = nx;

	result->right = right;
	result->left = left;

	if (reach == 0) {
		result->state = STATE_NO_PATH_DESC;				
		return;
	}	
	
	pylog("desc %i %i\n", nx->initial_inst->off,iidx);
	
	int * visited = new int[graph->nodes.size];

	i = iidx;
	
	flow_queue q;
	q.add(right);
	int ff = 0;
	memset(visited, 0, graph->nodes.size * sizeof(int));
	visited[right->idx] = 1;
	while (q.head) {
		int j;
		flow_node * n = q.remove_first();
		
		if (n == left) {
			continue;
		}

		int reach = graph->reachability_matrix.reach(left->idx, n->idx);
		
		if (reach > 0) {
			ff = 1;
			pylog("incongruence on %i\n", n->initial_inst->off);
			break;
		}
		for (j = 0; j < n->outgoing.size; j++) {
			flow_edge * e = earray_get(&n->outgoing, j, flow_edge*);
			flow_node * n2 = e->node;
			if (visited[n2->idx]) {
				continue;
			}
			visited[n2->idx] = 1;
			q.add(n2);
		}
	}

	if (ff) {
		// impossible if-else reached		
		result->state = STATE_PATH_INCONGRUENT;
	}
	else {
		// mind that the descendant here might be meaningless
		result->state = STATE_PATH;
		
	}	

	delete[] visited;
	



}

#undef pylog
#define pylog(...)