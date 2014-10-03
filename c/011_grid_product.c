/*
 * Find the largest product of N consecutive numbers in a grid
 * N is a command line parameter, the grid is read from stdin in the format:
 * <X = number of rows> <Y = number of columns> followed by X * Y integers
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "math_utils.h"

static int ** load_grid (int *, int *);
static void free_grid (int **, int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	int rows = 0;
	int columns = 0;

	int ** grid = load_grid (&rows, &columns);

	if (!grid)
		return 1;
	
	unsigned long max_product = 0;

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++) {
			unsigned long product = 1;

			if (j <= columns - N) {
				for (int k = 0; k < N; k++)
					product *= grid[i][j + k];

				max_product = MAX (product, max_product);
			}

			if (i <= rows - N) {
				product = 1;

				for (int k = 0; k < N; k++)
					product *= grid[i + k][j];

				max_product = MAX (product, max_product);
			}

			if (i <= rows - N && j <= columns - N) {
				product = 1;

				for (int k = 0; k < N; k++)
					product *= grid[i + k][j + k];

				max_product = MAX (product, max_product);
			}

			if (i >= N - 1 && j <= columns - N) {
				product = 1;

				for (int k = 0; k < N; k++)
					product *= grid[i - k][j + k];

				max_product = MAX (product, max_product);
			}
		}

	printf ("%lu\n", max_product);

	free_grid (grid, rows);

	return 0;
}

static int ** load_grid (int * rows_out, int * columns_out) {
	int rows = 0;
	int columns = 0;

	if (scanf ("%d %d", &rows, &columns) != 2)
		return NULL;
	else if (rows <= 0 || columns <= 0)
		return NULL;

	int ** grid = x_malloc (rows * sizeof (int *));

	for (int i = 0; i < rows; i++)
		grid[i] = x_malloc (columns * sizeof (int));

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++) {
			int value = 0;

			if (scanf ("%d", &value) != 1) {
				free_grid (grid, rows);
				return NULL;
			}

			grid[i][j] = value;
		}

	*rows_out = rows;
	*columns_out = columns;

	return grid;
}

static void free_grid (int ** grid, int rows) {
	for (int i = 0; i < rows; i++)
		free (grid[i]);

	free (grid);
}
