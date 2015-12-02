/*
 * Find the sum of the terms in the factorisation of M above N
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

static int count_multiples (int, int, int);

int main (int argc, char ** argv) {
	if (argc != 3) {
		fprintf (stderr, "usage: %s <M> <N>\n", argv[0]);
		return 1;
	}

	int M = atoi (argv[1]);
	int N = atoi (argv[2]);

	if (M < 0 || N < 0)
		return 1;

	if (N > M - N)
		N = M - N;

	size_t primes_count = 0;
	int * primes = primes_under (NULL, M + 1, &primes_count);

	/*
	 * n above k = {n * (n - 1) * ... * (n - k + 1)} / {k * (k - 1) * ... * 1}
	 *
	 * For each prime, count its occurences in the nominator and subtract the
	 * occurences in the denominator to arrive at the result
	 */

	long sum = 0;

	for (size_t i = 0; i < primes_count; i++) {
		int prime = primes[i];

		long count = 0;

		for (long mult = prime; mult <= M; mult *= prime) {
			count += count_multiples (M - N + 1, M, mult);
			count -= count_multiples (1, N, mult);
		}

		sum += prime * count;
	}

	printf ("%ld\n", sum);

	free (primes);

	return 0;
}

static int count_multiples (int from, int to, int mult) {
	int first = (from / mult) * mult;

	if (first == from)
		first -= mult;

	return (to - first) / mult;
}
