/*
 * Find the smallest denominator with a resilience less than a given fraction M / N
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

int main (int argc, char ** argv) {
	if (argc != 3) {
		fprintf (stderr, "usage: %s <M> <N>\n", argv[0]);
		return 1;
	}

	int M = atoi (argv[1]);
	int N = atoi (argv[2]);

	if (N <= 0 || M <= 0)
		return 1;

	/*
	 * We can calculate resilience of D as totient (D) / (D - 1)
	 * To minimise the ratio, we want totient to rise as slowly as possible
	 * and D to rise as quickly as possible
	 * From the relation between a prime factorisation and totient
	 * (see factors_to_totient () for details) it's obvious we want
	 * a product of the smallest number of primes raised to the power of 1
	 *
	 * This is an upper bound of the searched for denominator which
	 * is possibly needlessly low and can be improved by removing large primes
	 * and adding smaller ones to the factorisation to compensate
	 *
	 * Removing a prime p will decrease denominator by p, while decreasing the totient by (p - 1)
	 * Obviously, it makes sense to remove only the largest prime and add only the smallest one (2)
	 * enough times to re-lower the ratio to meet the criterion
	 */

	bool * sieve = eratosthenes_sieve (PRIMES_PRODUCT_LIMIT);

	long denominator = 1;
	long totient = 1;

	for (int i = 2; i < PRIMES_PRODUCT_LIMIT; i++) {
		if (!sieve[i])
			continue;

		denominator *= i;
		totient *= i - 1;

		if (totient * N < (denominator - 1) * M) {
			denominator /= i;
			totient /= i - 1;

			break;
		}
	}

	while (totient * N >= (denominator - 1) * M) {
		totient *= 2;
		denominator *= 2;
	}

	free (sieve);

	printf ("%ld\n", denominator);

	return 0;
}
