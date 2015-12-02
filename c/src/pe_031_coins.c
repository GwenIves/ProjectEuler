/*
 * Find the number of combinations of British coins that combine to make N pennies
 */

#include <stdio.h>
#include <stdlib.h>
#include "euler_utils.h"
#include "utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 0)
		return 1;

	int coin_values[] = {1, 2, 5, 10, 20, 50, 100, 200};

	printf ("%d\n", count_representation_combinations (coin_values, array_len (coin_values) - 1, N));

	return 0;
}
