#pragma once
#include "disasm.h"
#include "earray.h"

struct flow_node;

typedef struct flow_edge {
	int flags;
	struct flow_node * node;

	flow_edge() {
		memset(this, 0, sizeof(flow_edge));
	}

	flow_edge(flow_node * n) {
		memset(this, 0, sizeof(flow_edge));
		node = n;
	}

} flow_edge;

#define FLOW_EDGE_FLAG_LOOP			1
#define FLOW_EDGE_FLAG_IMPLICIT		2
#define FLOW_EDGE_FLAG_BREAK		4

typedef struct flow_node {
	flow_node * next;
	earray incoming;
	earray outgoing;
	int depth;
	int desired_depth;

	py_instruction * initial_inst;
	py_instruction * final_inst;
	int begin_off;
	uint32 flags;
	int end_off;
	int idx;
	int loop_block;

	void * stack_info;
	
	
	flow_node() {
		memset(this, 0, sizeof(flow_node));
		end_off = -1;
		desired_depth = -1;
	}

	void create_edge(flow_node * child) {
		flow_edge * e = new flow_edge(child);
		outgoing.add(e);
		child->incoming.add(this);
	}

	void add_child(flow_node * child, int direction) {
		py_assert(direction == 1 || direction == -1, "bad flow graph node direction");
		if (direction == 1) {
			flow_edge * e = new flow_edge(child);
			outgoing.add(e);
		}
		else if (direction == -1) {
			incoming.add(child);
		}

	}

	flow_node * split(int off, py_instruction * prev, py_instruction * next) {
		if (end_off > -1) {
			py_assert(off > begin_off && off < end_off, "Flow graph has invalid offset");
		}
		else {
			py_assert(off > begin_off, "Flow graph has invalid offset");

		}

		flow_node * new_node = new flow_node();
		new_node->begin_off = off;
		new_node->end_off = end_off;
		py_assert(next != NULL, "Bad instruction on node split");
		new_node->initial_inst = next;
		end_off = off;
		new_node->final_inst = final_inst;
		final_inst = prev;
		
		new_node->outgoing.copy(&outgoing);
		
		outgoing.clear();
		flow_edge * e = new flow_edge(new_node);
		outgoing.add(e);

		int l; 
		for (l = 0; l < new_node->outgoing.size; l++) {
			flow_edge * e1 = earray_get(&new_node->outgoing, l, flow_edge*);
			flow_node * x = e1->node;
			int i;
			int f = 0;
			for (i = 0; i < x->incoming.size; i++) {
				flow_node * inc = earray_get(&x->incoming, i, flow_node*);
				
				if (inc == this) {
					x->incoming.replace(i, new_node);
					f = 1;
					break;
				}
				
			}
			py_assert(f, "Incoming node not found on node split");
		}

		new_node->incoming.add(this);
		return new_node;
	}
} flow_node;

typedef struct graph_reachability {
	int * data;
	int n;
	graph_reachability() {
		data = NULL;
	}

	graph_reachability(int in) {
		n = in;
		data = new int[n*n];
		memset(data, 0, n*n*sizeof(int));
	}

	int reach(int i, int j) {
		return data[i*n + j];
	}

	void set_reach(int i, int j, int dist) {
		data[i*n + j] = dist;
	}
} graph_reachability;

typedef struct flow_graph {
	flow_graph() {

	}
	earray nodes;
	graph_reachability reachability_matrix;
} flow_graph;

enum FLOW_RIGHT_LEFT_STATE {
	STATE_NO_PATH,
	STATE_NO_PATH_DESC,
	STATE_PATH,
	STATE_PATH_INCONGRUENT
};

#define FLOW_LR_RESULT_LOOPED	1

typedef struct flow_left_right_result {
	int state;
	int flags;
	flow_node * desc;
	flow_node * right;
	flow_node * left;

} flow_left_right_result;

typedef struct flow_queue {
	flow_node * head;
	flow_node * tail;
	flow_queue() {
		head = tail = NULL;
	}

	void add(flow_node * node) {
		
		node->next = NULL;
		if (head == NULL) {
			head = tail = node;
		}
		else {
			tail->next = node;
			tail = node;
		}
	}

	flow_node * remove_first() {
		flow_node * t = head;
		if (head == tail) {
			head = tail = NULL;
		}
		else {
			head = head->next;
		}
		return t;
	}

} flow_queue;

#define FLOW_FLAG_EXCEPTION			(1<<0)
#define FLOW_FLAG_FINALLY			(1<<1)
#define FLOW_FLAG_PURE_CONDITIONAL	(1<<2)
#define FLOW_FLAG_ELSE_CONDITIONAL	(1<<3)


flow_node * flow_closest_descendant(flow_graph * graph, flow_node * n1, flow_node * n2);
void build_flow(py_instruction * instruction_set, int instruction_set_size, flow_graph * output, char * name);
void flow_left_right_reachability(flow_node * n, flow_graph * graph, flow_left_right_result * result);
flow_node * flow_get_node_from_instruction(flow_graph * graph, py_instruction * inst);
flow_node * flow_get_node_from_offset(flow_graph * graph, int offset);
int flow_count_non_loop_incoming(flow_node * n);
flow_node * flow_loop_get_non_looped(flow_node *n);
int flow_is_loop(flow_node * n1, flow_node * n2);

