/*
 * Find the number of combinations of British coins that combine to make N pennies
 */

#include <stdio.h>
#include <stdlib.h>

#define COIN_TYPES	8

static int count_combinations (int *, int, int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 0)
		return 1;

	int coin_values[COIN_TYPES] = {1, 2, 5, 10, 20, 50, 100, 200};

	printf ("%d\n", count_combinations (coin_values, COIN_TYPES - 1, N));

	return 0;
}

static int count_combinations (int * values, int max_value, int sum) {
	int combinations = 0;

	if (sum > 0 && sum % values[max_value] == 0)
		combinations++;

	if (max_value > 0)
		while (sum > 0) {
			combinations += count_combinations (values, max_value - 1, sum);
			sum -= values[max_value];
		}

	return combinations;
}
