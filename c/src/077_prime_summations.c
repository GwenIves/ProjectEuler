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

	bool * sieve = eratosthenes_sieve (upper_bound + 1);

	int primes[N];
	size_t primes_count = 0;

	for (int i = 2; i <= upper_bound ; i++)
		if (sieve[i])
			primes[primes_count++] = i;

	int sum = 2;

	while (count_representation_combinations (primes, primes_count - 1, sum) < N)
		sum++;

	printf ("%d\n", sum);

	free (sieve);

	return 0;
}
