/*
 * Find the value of the maximum path from the top to the bottom of a numeric triangle read from stdin
 * The triangle is read in a format <N = rows count> followed by all the numbers on and under a diagonal
 * of an N x N square one row at a time left to right
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"
#include "utils.h"

int main () {
	int rows = 0;

	int ** triangle = load_triangle (&rows);

	if (!triangle)
		return 1;

	for (int i = rows - 2; i >= 0; i--)
		for (int j = 0; j <= i; j++)
			triangle[i][j] += MAX (triangle[i + 1][j], triangle[i + 1][j + 1]);

	printf ("%d\n", triangle[0][0]);

	free_matrix (triangle, rows);

	return 0;
}
