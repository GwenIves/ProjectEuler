/*
 * Find the smallest positive number that can be represented as a sum of at least N primes
 */

#include <stdio.h>
#include <stdlib.h>
#include "euler_utils.h"
#include "math_utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 0)
		return 1;

	// Worst case upper bound - sum of N twos
	int upper_bound = 2 * N;

	size_t primes_count = 0;
	int * primes = primes_under (NULL, upper_bound + 1, &primes_count);

	int sum = 2;

	while (count_representation_combinations (primes, primes_count - 1, sum) < N)
		sum++;

	printf ("%d\n", sum);

	free (primes);

	return 0;
}
