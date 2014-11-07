/*
 * Find the sum of all primes below N
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 0) {
		printf ("0\n");
		return 0;
	}

	bool * sieve = eratosthenes_sieve (N);

	unsigned long sum = 0;

	for (int i = 2; i < N; i++)
		if (sieve[i])
			sum += i;

	printf ("%lu\n", sum);

	free (sieve);

	return 0;
}
