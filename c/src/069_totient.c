/*
 * Find the number n, 1 <= n <= N, such that n / Totient (n) is maximal
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

#define MAX_PRIMES	100

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1)
		return 1;

	/*
	 * Totient (p^k) for all primes p = p^k - p^(k - 1)
	 * For a, b coprime, Totient (a * b) = Totient (a) * Totient (b)
	 *
	 * Consequently, given n with i prime factors, n = product of p_i^q_i
	 * and Totient (n) = product (p_i^q_i - p_i^(q_i - 1)) = n * product (1 - 1 / p_i)
	 *
	 * n / Totient (n) is then equal to product (p_i / (p_i - 1))
	 * And this value will be maximal for the product of the largest number of smallest primes
	 */

	bool * sieve = eratosthenes_sieve (MAX_PRIMES);

	int max = 1;

	for (int i = 2; i < MAX_PRIMES; i++) {
		if (!sieve[i])
			continue;

		if (max * i > N)
			break;
		else
			max *= i;
	}

	printf ("%d\n", max);

	free (sieve);

	return 0;
}
