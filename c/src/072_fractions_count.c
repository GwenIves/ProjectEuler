/*
 * Find how many reduced proper fractions a/b exist for b less than or equal to N
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"
#include "utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 0)
		return 1;

	// For each denominator there is exactly Totient (denominator) reduced proper fractions
	// Totient (x) = x * Product (1 - 1 / p) for all primes p dividing x

	bool * sieve = eratosthenes_sieve (N + 1);
	int * totients = x_malloc ((N + 1) * sizeof (int));

	for (int i = 2; i <= N; i++)
		totients[i] = i;

	for (int i = 2; i <= N; i++) {
		if (!sieve[i])
			continue;

		for (int j = i; j <= N; j += i) {
			totients[j] /= i;
			totients[j] *= i - 1;
		}
	}

	long count = 0;

	for (int i = 2; i <= N; i++)
		count += totients[i];

	printf ("%ld\n", count);

	free (sieve);
	free (totients);

	return 0;
}
