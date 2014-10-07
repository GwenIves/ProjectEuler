/*
 * Find the smallest number divisible by all the numbers from 1 to N
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

	if (N <= 0)
		return 1;

	unsigned long num = 1;
	char * primes = eratosthenes_sieve (N + 1);

	double log_N = log (N);

	for (int i = 2; i <= N; i++)
		if (primes[i]) {
			int pow = log_N / log (i);

			for (int j = 0; j < pow; j++)
				num *= i;
		}

	printf ("%lu\n", num);

	free (primes);

	return 0;
}
