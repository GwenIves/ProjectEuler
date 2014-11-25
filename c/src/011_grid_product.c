/*
 * Find the largest product of N consecutive numbers in a grid
 * N is a command line parameter, the grid is read from stdin in the format:
 * <X = number of rows> <Y = number of columns> followed by X * Y integers
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "math_utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 0)
		return 1;

	int rows = 0;
	int columns = 0;

	int ** grid = load_matrix (&rows, &columns);

	if (!grid)
		return 1;
	
	long max_product = 0;

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++) {
			long product = 1;

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

	printf ("%ld\n", max_product);

	free_matrix (grid, rows);

	return 0;
}
