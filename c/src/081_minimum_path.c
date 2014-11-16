/*
 * Find the value of the minimum path from the left top to the right bottom corner of a numeric matrix
 * It is only possible to move right or down. The matrix is read from stdin in this format:
 * <N = rows and columns count> on a separete line, followed by comma separated numbers, N per line
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"
#include "utils.h"

static int ** load_matrix (int *);
static void free_matrix (int **, int);

int main () {
	int rows = 0;

	int ** matrix = load_matrix (&rows);

	if (!matrix)
		return 1;

	for (int i = rows - 1; i >= 0; i--)
		for (int j = rows - 1; j >= 0; j--) {
			if ((i == rows - 1) && (j == rows - 1))
				continue;
			else if (i == rows - 1)
				matrix[i][j] += matrix[i][j + 1];
			else if (j == rows - 1)
				matrix[i][j] += matrix[i + 1][j];
			else
				matrix[i][j] += MIN (matrix[i + 1][j], matrix[i][j + 1]);
		}

	printf ("%d\n", matrix[0][0]);

	free_matrix (matrix, rows);

	return 0;
}

static int ** load_matrix (int * rows_out) {
	int rows = 0;

	if (scanf ("%d\n", &rows) != 1)
		return NULL;
	else if (rows <= 0)
		return NULL;

	int ** matrix = x_malloc (rows * sizeof (int *));

	for (int i = 0; i < rows; i++) {
		matrix[i] = x_malloc (rows * sizeof (int));

		for (int j = 0; j < rows; j++) {
			int value = 0;

			if (scanf ("%d", &value) != 1) {
				free_matrix (matrix, i);
				return NULL;
			}

			matrix[i][j] = value;

			(void) fgetc (stdin);
		}
	}

	*rows_out = rows;

	return matrix;
}

static void free_matrix (int ** matrix, int rows) {
	free_array (matrix, rows);
	free (matrix);
}
