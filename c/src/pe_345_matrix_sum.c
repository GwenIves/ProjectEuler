/*
 * Find the maximum sum of a square matrix read from stdin such that
 * exactly one element is chosen from each row and column.
 * The stdin format should be:
 * number of rows, number of columns, followed by space separated matrix values
 */

#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"
#include "math_utils.h"
#include "utils.h"

int main (void) {
	int rows = 0;
	int ** matrix = load_square (&rows);

	if (!matrix)
		return 1;

	int max_sum = 0;

	hash_table_t * max_sums = hash_table_create (rows * 1000);

	for (int row = 0; row < rows; row++) {
		char free_columns[rows + 1];

		for (int i = 0; i < rows; i++)
			if (i <= row)
				free_columns[i] = '1';
			else
				free_columns[i] = '0';

		free_columns[rows] = '\0';

		do {
			bool first_sum = true;
			max_sum = 0;

			for (int i = 0; i < rows; i++) {
				if (free_columns[i] == '0')
					continue;

				if (row == 0) {
					max_sum = matrix[row][i];
				} else {
					free_columns[i] = '0';

					int sum = matrix[row][i] + *hash_table_fetch (max_sums, free_columns, int);

					free_columns[i] = '1';

					if (first_sum || sum > max_sum) {
						first_sum = false;
						max_sum = sum;
					}
				}
			}

			hash_table_insert (max_sums, free_columns, copy_int (max_sum));
		} while (prev_permutation (free_columns));
	}

	printf ("%d\n", max_sum);

	hash_table_free (max_sums);
	free_matrix (matrix, rows);

	return 0;
}
