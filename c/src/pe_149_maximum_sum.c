/*
 * Find the maximum consecutive subsequence sum in an N x N matrix filled with a Lagged Fibonacci random number generator
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "random.h"

static int ** allocate_random_matrix (int);
static int find_maximum (int **, int);
static int find_maximum_row (int **, int, int);
static int find_maximum_column (int **, int, int);
static int find_maximum_diagonal (int **, int, int, int);
static int find_maximum_anti_diagonal (int **, int, int, int);
static int find_max_subsequence (const int *, int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1)
		return 1;

	int ** matrix = allocate_random_matrix (N);

	printf ("%d\n", find_maximum (matrix, N));

	free_matrix (matrix, N);

	return 0;
}

static int find_maximum (int ** matrix, int size) {
	int maximum = matrix[0][0];
	int new_maximum = 0;

	for (int i = 0; i < size; i++) {
		if ((new_maximum = find_maximum_row (matrix, size, i)) > maximum)
			maximum = new_maximum;

		if ((new_maximum = find_maximum_column (matrix, size, i)) > maximum)
			maximum = new_maximum;
	}

	for (int i = 0; i < size; i++) {
		if ((new_maximum = find_maximum_diagonal (matrix, size, 0, i)) > maximum)
			maximum = new_maximum;

		if ((new_maximum = find_maximum_anti_diagonal (matrix, size, size - 1, i)) > maximum)
			maximum = new_maximum;
	}

	for (int i = 1; i < size; i++) {
		if ((new_maximum = find_maximum_diagonal (matrix, size, i, 0)) > maximum)
			maximum = new_maximum;

		if ((new_maximum = find_maximum_anti_diagonal (matrix, size, size - i - 1, 0)) > maximum)
			maximum = new_maximum;
	}

	return maximum;
}

static int find_max_subsequence (const int * values, int size) {
	int max = values[0];
	int new_max = 0;

	for (int i = 0; i < size; i++) {
		new_max += values[i];

		if (new_max > max)
			max = new_max;

		if (new_max < 0)
			new_max = 0;
	}

	return max;
}

static int find_maximum_row (int ** matrix, int size, int row) {
	int values[size];

	for (int i = 0; i < size; i++)
		values[i] = matrix[row][i];

	return find_max_subsequence (values, size);
}

static int find_maximum_column (int ** matrix, int size, int column) {
	int values[size];

	for (int i = 0; i < size; i++)
		values[i] = matrix[i][column];

	return find_max_subsequence (values, size);
}

static int find_maximum_diagonal (int ** matrix, int size, int row, int column) {
	int values[size];

	int i = 0;

	while (row < size && column < size) {
		values[i] = matrix[row][column];

		i++;
		row++;
		column++;
	}

	return find_max_subsequence (values, i);
}

static int find_maximum_anti_diagonal (int ** matrix, int size, int row, int column) {
	int values[size];

	int i = 0;

	while (row >= 0 && column < size) {
		values[i] = matrix[row][column];

		i++;
		row--;
		column++;
	}

	return find_max_subsequence (values, i);
}


static int ** allocate_random_matrix (int size) {
	int ** matrix = x_malloc (size * sizeof (int *));

	for (int i = 0; i < size; i++) {
		int * row = x_malloc (size * sizeof (int));

		for (int j = 0; j < size; j++)
			row[j] = next_lfg_s ();

		matrix[i] = row;
	}

	return matrix;
}
