/*
 * Find the product of a and b where |a| < N and |b| < N
 * for which the quadratic formula x^2 + a*x + b, x>= 0, produces the largest number of consecutive primes
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

static int formula_primes (bool *, int, int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 1)
		return 1;

	// When x reaches b, the formula cannot certainly produce a prime
	int formula_maximum = 2 * N * N - 3 * N + 1;

	bool * primes = eratosthenes_sieve (formula_maximum + 1);

	int max_primes = 0;
	int max_a = 0;
	int max_b = 0;

	for (int a = -N + 1; a <= N - 1; a++) {
		for (int b = -N + 1; b <= N - 1; b++) {
			// b must be a prime or the formula will certainly not produce a prime for x = 0
			if (!primes[ABS (b)])
				continue;

			int primes_count = formula_primes (primes, a, b);

			if (primes_count >= max_primes) {
				max_primes = primes_count;
				max_a = a;
				max_b = b;
			}
		}
	}

	printf ("%d\n", max_a * max_b);

	free (primes);

	return 0;
}

static int formula_primes (bool * primes, int a, int b) {
	int x = 0;
	int primes_count = 0;

	while (true) {
		int value = x * (x + a) + b;

		if (primes[ABS (value)]) {
			primes_count++;
			x++;
		} else
			break;
	}

	return primes_count;
}
