/*
 * Find the value of the minimum path from the left to the right column of a numeric matrix
 * It is possible to move right, up or down. The matrix is read from stdin in this format:
 * <N = rows count> <N = columns count> on a separete line, followed by comma separated numbers, N per line
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"
#include "utils.h"

static int down_cost (int **, int, int, int, int);

int main () {
	int rows = 0;

	int ** matrix = load_square (&rows);

	if (!matrix)
		return 1;

	for (int j = rows - 2; j >= 0; j--)
		for (int i = 0; i < rows; i++) {
			int up_or_right = 0;

			if (i == 0)
				up_or_right = matrix[i][j + 1];
			else
				up_or_right = MIN (matrix[i][j + 1], matrix[i - 1][j]);

			int down = down_cost (matrix, rows, i, j, up_or_right);

			matrix[i][j] += MIN (up_or_right, down);
		}

	int min = matrix[0][0];

	for (int i = 1; i < rows; i++)
		if (matrix[i][0] < min)
			min = matrix[i][0];

	printf ("%d\n", min);

	free_matrix (matrix, rows);

	return 0;
}

static int down_cost (int ** matrix, int rows, int i, int j, int up_or_right) {
	int down = 0;
	int min = up_or_right;

	for (int k = i + 1; k < rows; k++) {
		down += matrix[k][j];

		if (down >= min)
			break;

		int total_cost = down + matrix[k][j + 1];

		if (total_cost < min)
			min = total_cost;
	}

	return min;
}
