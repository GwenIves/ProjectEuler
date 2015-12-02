/*
 * Find the value of the minimum path from the left top to the right bottom corner of a numeric matrix
 * It is only possible to move right or down. The matrix is read from stdin in this format:
 * <N = rows count> <N = columns count> on a separete line, followed by comma separated numbers, N per line
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"
#include "utils.h"

int main (void) {
	int rows = 0;

	int ** matrix = load_square (&rows);

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
