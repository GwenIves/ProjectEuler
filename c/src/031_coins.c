/*
 * Find the number of combinations of British coins that combine to make N pennies
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#define COIN_TYPES	8

static int count_combinations (int *, int, int, int **);
static int ** allocate_cache (size_t, size_t);
static void free_cache (int **, size_t);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 0)
		return 1;

	int coin_values[COIN_TYPES] = {1, 2, 5, 10, 20, 50, 100, 200};

	int ** cache = allocate_cache (COIN_TYPES, N + 1);

	printf ("%d\n", count_combinations (coin_values, COIN_TYPES - 1, N, cache));

	free_cache (cache, COIN_TYPES);

	return 0;
}

static int count_combinations (int * values, int max_value, int sum, int ** cache) {
	int combinations = 0;

	if (cache[max_value][sum] == -1) {
		// One representation using only max_value coins
		if (sum > 0 && sum % values[max_value] == 0)
			combinations++;

		if (max_value > 0) {
			int remaining_sum = sum;

			while (remaining_sum > 0) {
				combinations += count_combinations (values, max_value - 1, remaining_sum, cache);
				remaining_sum -= values[max_value];
			}
		}

		cache[max_value][sum] = combinations;
	} else
		combinations = cache[max_value][sum];

	return combinations;
}

static int ** allocate_cache (size_t rows, size_t columns) {
	int ** cache = x_malloc (rows * sizeof (int *));

	for (size_t i = 0; i < rows; i++) {
		cache[i] = x_malloc (columns * sizeof (int));

		for (size_t j = 0; j < columns; j++)
			cache[i][j] = -1;
	}

	return cache;
}

static void free_cache (int ** cache, size_t rows) {
	for (size_t i = 0; i < rows; i++)
		free (cache[i]);

	free (cache);
}
