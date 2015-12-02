/*
 * Find the value of the minimum path from the top left to the bottom right corner of a numeric matrix
 * It is possible to move right, left, up or down. The matrix is read from stdin in this format:
 * <N = rows count> <N = columns count> on a separete line, followed by comma separated numbers, N per line
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "linked_list.h"

#define INFINITY -1

static void update_costs (int **, linked_list_t *, bool **, int, int, int, int);

int main (void) {
	int rows = 0;

	int ** matrix = load_square (&rows);

	if (!matrix)
		return 1;

	int ** costs = allocate_matrix (rows, rows, INFINITY);
	bool ** visited = allocate_matrix (rows, rows, (bool) false);

	linked_list_t * neighbours = linked_list_create ();

	costs[0][0] = 0;

	int * n_ptr = linked_list_append_empty_array (neighbours, 2, int);

	n_ptr[0] = 0;
	n_ptr[1] = 0;

	while (true) {
		int min_i = -1;
		int min_j = -1;
		int * min_neighbour = NULL;

		while ((n_ptr = linked_list_next (neighbours, int)) != NULL) {
			int i = n_ptr[0];
			int j = n_ptr[1];

			if (min_i < 0 || costs[i][j] < costs[min_i][min_j]) {
				min_i = i;
				min_j = j;
				min_neighbour = n_ptr;
			}
		}

		visited[min_i][min_j] = true;
		costs[min_i][min_j] += matrix[min_i][min_j];

		linked_list_delete (neighbours, min_neighbour);

		if (min_i == (rows - 1) && min_j == (rows - 1)) {
			printf ("%d\n", costs[min_i][min_j]);
			break;
		}

		int cost = costs[min_i][min_j];

		update_costs (costs, neighbours, visited, rows, cost, min_i, min_j + 1);
		update_costs (costs, neighbours, visited, rows, cost, min_i, min_j - 1);
		update_costs (costs, neighbours, visited, rows, cost, min_i + 1, min_j);
		update_costs (costs, neighbours, visited, rows, cost, min_i - 1, min_j);
	}

	free_matrix (matrix, rows);
	free_matrix (costs, rows);
	free_matrix (visited, rows);

	linked_list_free (neighbours);

	return 0;
}

static void update_costs (int ** costs, linked_list_t * neighbours, bool ** visited, int rows, int weight, int i, int j) {
	if (i < 0 || i >= rows)
		return;

	if (j < 0 || j >= rows)
		return;

	if (visited[i][j])
		return;

	if (costs[i][j] == INFINITY) {
		costs[i][j] = weight;

		int * n_ptr = linked_list_append_empty_array (neighbours, 2, int);

		n_ptr[0] = i;
		n_ptr[1] = j;
	} else if (costs[i][j] > weight)
		costs[i][j] = weight;
}
