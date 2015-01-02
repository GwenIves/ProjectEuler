/*
 * Find the sum of all integers n under N such that for all divisors d of n, d + n / d is a prime
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "math_utils.h"

static bool is_generating (int, bool *);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 1)
		return 1;

	bool * sieve = eratosthenes_sieve (N + 1);

	long sum = 1;

	/*
	 * 1. For each candidate i, i + 1 must be prime (from definition when d == 1)
	 * 2. In general, i cannot contain any prime factor f with a power larger than 1
	 *    otherwise, d + n/d would not be a prime when d == f
	 * 3. We only need to check i == 2 (mod 4) because i (except 1) cannot be odd (from point 1.)
	 *    and 4 cannot divide i (from point 2.)
	 */
	for (int i = 2; i < N; i += 4) {
		if (!sieve[i + 1])
			continue;
		else if (i % 9 == 0)
			continue;
		else if (is_generating (i, sieve))
			sum += i;
	}

	printf ("%ld\n", sum);

	free (sieve);

	return 0;
}

static bool is_generating (int num, bool * sieve) {
	int divisor_limit = sqrt (num);

	for (int i = 2; i <= divisor_limit; i++) {
		if (num % i != 0)
			continue;

		if (!sieve[i + num / i])
			return false;
	}

	return true;
}
