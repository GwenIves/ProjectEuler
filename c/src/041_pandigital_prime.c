/*
 * Find the largest N-pandigital prime
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "math_utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1 || N > 9)
		return 1;

	bool * primes = eratosthenes_sieve (sqrt (pow (10, N)) + 1);

	char digits[DIGITS_COUNT];
	int digit = 0;

	for (int i = N; i > 0; i--)
		digits[digit++] = i + '0';

	digits[digit] = '\0';

	while (prev_permutation (digits)) {
		if (is_prime (primes, atoi (digits))) {
			printf ("%s\n", digits);
			break;
		}
	}

	free (primes);

	return 0;
}
