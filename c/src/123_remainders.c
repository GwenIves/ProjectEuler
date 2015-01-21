/*
 * Find the smallest n for which the remainder of dividing (p_n - 1)^n + (p_n + 1)^n by p_n^2 first exceeds N, p_n denotes the n-th prime
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "math_utils.h"

static long get_remainder (int, int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	long N = atol (argv[1]);

	if (N < 0)
		return 1;
	else if (N == 0) {
		// Handle the only even prime, 2, separately to simplify the remainder calculation
		printf ("1\n");
		return 0;
	}

	int limit = 5 * sqrt (N);
	int prime = 3;
	int n = 1;

	while (true) {
		bool * primes = eratosthenes_sieve (limit);

		while (prime < limit) {
			if (primes[prime]) {
				n++;

				if (get_remainder (prime, n) > N) {
					printf ("%d\n", n);

					free (primes);
					return 0;
				}
			}

			prime += 2;
		}

		free (primes);
		limit *= 10;
	}

	return 0;
}

// See comments in problem 120 for explanation of the remainder calculation
static long get_remainder (int prime, int n) {
	if (n % 2 == 0)
		return 2;
	else
		return (2L * n * prime) % ((long) prime * prime);
}
