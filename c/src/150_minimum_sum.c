/*
 * Find the minimum subtriangle sum in an N lines triangular array filled with a Linear Congruent random number generator
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

static int next_lcg (void);
static int ** allocate_random_triangle (int);
static int ** precompute_sums (int **, int);
static long find_minimum (int **, int);
static long find_min_subtriangle (int **, int, int, int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1)
		return 1;

	int ** triangle = allocate_random_triangle (N);
	int ** sums = precompute_sums (triangle, N);

	free_matrix (triangle, N);

	printf ("%ld\n", find_minimum (sums, N));

	free_matrix (sums, N);

	return 0;
}

static long find_minimum (int ** sums, int size) {
	long minimum = sums[0][0];

	for (int i = 0; i < size; i++)
		for (int j = 0; j <= i; j++) {
			long sub_tree_minimum = find_min_subtriangle (sums, size, i, j);

			if (sub_tree_minimum < minimum)
				minimum = sub_tree_minimum;
		}

	return minimum;
}

static long find_min_subtriangle (int ** sums, int size, int start_row, int start_column) {
	long minimum = sums[start_row][start_column] - (start_column > 0 ? sums[start_row][start_column - 1] : 0);
	long new_minimum = minimum;

	for (int i = start_row + 1, end_column = start_column + 1; i < size; i++, end_column++) {
		new_minimum += sums[i][end_column] - (start_column > 0 ? sums[i][start_column - 1] : 0);

		if (new_minimum < minimum)
			minimum = new_minimum;
	}

	return minimum;
}

static int ** allocate_random_triangle (int size) {
	int ** triangle = x_malloc (size * sizeof (int *));

	for (int i = 0; i < size; i++) {
		int * row = x_malloc ((i + 1) * sizeof (int));

		for (int j = 0; j <= i; j++)
			row[j] = next_lcg ();

		triangle[i] = row;
	}

	return triangle;
}

static int ** precompute_sums (int ** triangle, int size) {
	int ** sums = x_malloc (size * sizeof (int *));

	for (int i = 0; i < size; i++) {
		int * row = x_malloc ((i + 1) * sizeof (int));

		row[0] = triangle[i][0];

		for (int j = 1; j <= i; j++)
			row[j] = row[j - 1] + triangle[i][j];

		sums[i] = row;
	}

	return sums;
}

#define MOD	(1 << 20)
#define SUB	(1 << 19)

static int next_lcg (void) {
	static int t = 0;

	t = (615949L * t + 797807) % MOD;

	return t - SUB;
}
