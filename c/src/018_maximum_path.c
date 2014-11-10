/*
 * Find the value of the maximum path from the top to the bottom of a numeric triangle read from stdin
 * The triangle is read in a format <N = rows count> followed by all the numbers on and under a diagonal
 * of an N x N square one row at a time left to right
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"
#include "utils.h"

static int ** load_triangle (int *);
static void free_triangle (int **, int);

int main () {
	int rows = 0;

	int ** triangle = load_triangle (&rows);

	if (!triangle)
		return 1;

	for (int i = rows - 2; i >= 0; i--)
		for (int j = 0; j <= i; j++)
			triangle[i][j] += MAX (triangle[i + 1][j], triangle[i + 1][j + 1]);

	printf ("%d\n", triangle[0][0]);

	free_triangle (triangle, rows);

	return 0;
}

static int ** load_triangle (int * rows_out) {
	int rows = 0;

	if (scanf ("%d", &rows) != 1)
		return NULL;
	else if (rows <= 0)
		return NULL;

	int ** triangle = x_malloc (rows * sizeof (int *));

	for (int i = 0; i < rows; i++)
		triangle[i] = x_malloc ((i + 1) * sizeof (int));

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < i + 1; j++) {
			int value = 0;

			if (scanf ("%d", &value) != 1) {
				free_triangle (triangle, rows);
				return NULL;
			}

			triangle[i][j] = value;
		}

	*rows_out = rows;

	return triangle;
}

static void free_triangle (int ** triangle, int rows) {
	free_array (triangle, rows);
	free (triangle);
}
