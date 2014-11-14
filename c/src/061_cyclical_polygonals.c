/*
 * Find the sums of all ordered N-digit six-tuples of polygonals (triangle to octagon) that are 2-digit cyclical
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "math_utils.h"
#include "linked_list.h"

#define POLY_COUNT	6

typedef long (* poly_func_t) ();

static poly_func_t polygonal_functions[] = {
	next_triangle_num,
	next_square_num,
	next_pentagonal_num,
	next_hexagonal_num,
	next_heptagonal_num,
	next_octagonal_num
};

typedef struct {
	int prefix;
	int suffix;
	long value;
} cycle_node_t;

static void get_polygonals (linked_list_t **, int);
static void free_polygonals (linked_list_t **);
static bool is_valid_link (int);
static void find_all_cycles (linked_list_t **, long, int, int, int);
static void shuffle_order (char *, linked_list_t **, linked_list_t **);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 4)
		return 1;

	linked_list_t * nodes[POLY_COUNT];

	get_polygonals (nodes, N);

	char polygonals_order[] = "012345"; 

	do {
		linked_list_t * shuffled[POLY_COUNT];

		shuffle_order (polygonals_order, nodes, shuffled);

		find_all_cycles (shuffled, 0, 0, 0, 0);
	} while (next_permutation (polygonals_order + 1));

	free_polygonals (nodes);

	return 0;
}

static void shuffle_order (char * new_order, linked_list_t ** nodes, linked_list_t ** shuffled_nodes) {
	for (int i = 0; i < POLY_COUNT; i++) {
		int new_index = new_order[i] - '0';

		shuffled_nodes[i] = nodes[new_index];
	}
}

// Recursively look for all cycles i <-> i+1, POLY_COUNT-1 <-> 0, linked by the "nodes" lists and print out their sums
static void find_all_cycles (linked_list_t ** nodes, long sum, int start, int connected_by, int connecting_to) {
	cycle_node_t * n = NULL;

	if (start == 0) {
		while ((n = linked_list_next (nodes[start], cycle_node_t)) != NULL)
			find_all_cycles (nodes, n->value, start + 1, n->suffix, n->prefix);
	} else if (start == POLY_COUNT - 1) {
		while ((n = linked_list_next (nodes[start], cycle_node_t)) != NULL)
			if (n->prefix == connected_by && n->suffix == connecting_to) {
				sum += n->value;

				printf ("%ld\n", sum);
			}
	} else {
		while ((n = linked_list_next (nodes[start], cycle_node_t)) != NULL) {
			if (n->prefix == connected_by)
				find_all_cycles (nodes, sum + n->value, start + 1, n->suffix, connecting_to);
		}
	}
}

static void get_polygonals (linked_list_t ** nodes, int digits) {
	int start = pow (10, digits - 1);
	int end = start * 10;

	for (int i = 0; i < POLY_COUNT; i++) {
		nodes[i] = linked_list_create ();

		while (true) {
			long num = polygonal_functions[i] ();

			if (num < start)
				continue;
			else if (num >= end)
				break;
			else {
				cycle_node_t node;

				node.value = num;
				node.suffix = num % 100;
				node.prefix = num;

				while (node.prefix > 100)
					node.prefix /= 100;

				if (!is_valid_link (node.suffix) || !is_valid_link (node.prefix))
					continue;

				cycle_node_t * n = linked_list_append_empty (nodes[i], cycle_node_t);

				*n = node;
			}
		}
	}
}

static void free_polygonals (linked_list_t ** nodes) {
	for (int i = 0; i < POLY_COUNT; i++)
		linked_list_free (nodes[i]);
}

// Check that num is a valid cycle link with 2 non zero digits
static bool is_valid_link (int num) {
	if (num < 10)
		return false;
	else if (num % 10 == 0)
		return false;

	return true;
}
