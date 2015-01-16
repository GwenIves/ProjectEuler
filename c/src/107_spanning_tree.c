/*
 * Find the weight difference between a connected weighted undirected graph
 * and its minimum spanning tree
 * The graph is read from stdin in matrix format
 * The matrix should be preceded by row count X, column count Y,
 * X = Y = vertex count, weight 0 means no connection between vertices
 */

#include <stdio.h>
#include <stdbool.h>
#include "utils.h"

static int graph_weight (int **, int);

int main () {
	int vertex_count = 0;

	int ** matrix = load_square (&vertex_count);
	int ** spanning_tree = allocate_matrix (vertex_count, vertex_count, 0);
	bool * vertex_connected = allocate_array (vertex_count, (bool) false);

	if (vertex_count == 0)
		return 1;

	vertex_connected[0] = true;

	for (int pass = 1; pass < vertex_count; pass++) {
		int minimum_edge = -1;
		int min_i = 0;
		int min_j = 0;

		for (int i = 0; i < vertex_count; i++) {
			if (!vertex_connected[i])
				continue;

			for (int j = 0; j < vertex_count; j++) {
				if (matrix[i][j] == 0)
					continue;

				if (vertex_connected[j])
					continue;

				if (minimum_edge == -1 || matrix[i][j] < minimum_edge) {
					minimum_edge = matrix[i][j];
					min_i = i;
					min_j = j;
				}
			}
		}

		spanning_tree[min_i][min_j] = minimum_edge;
		spanning_tree[min_j][min_i] = minimum_edge;

		vertex_connected[min_j] = true;
	}

	printf ("%d\n", graph_weight (matrix, vertex_count) - graph_weight (spanning_tree, vertex_count));

	free_matrix (matrix, vertex_count);
	free_matrix (spanning_tree, vertex_count);
	free (vertex_connected);

	return 0;
}

static int graph_weight (int ** matrix, int vertex_count) {
	int weight = 0;

	for (int i = 0; i < vertex_count; i++)
		for (int j = i + 1; j < vertex_count; j++)
			weight += matrix[i][j];

	return weight;
}
