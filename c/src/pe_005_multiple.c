/*
 * Find the smallest number divisible by all the numbers from 1 to N
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

	if (N <= 0)
		return 1;

	long num = 1;
	bool * primes = eratosthenes_sieve (N + 1);

	// The result will have to be divisible by all primes and their composite powers less than or equal to N
	for (int i = 2; i <= N; i++) {
		if (primes[i]) {
			int power = 1;

			while (power < N)
				power *= i;

			if (power > N)
				power /= i;

			num *= power;
		}
	}

	printf ("%ld\n", num);

	free (primes);

	return 0;
}
