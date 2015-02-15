/*
 * Find the sum of all primes under N that produce totient chains of length M
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

int main (int argc, char ** argv) {
	if (argc != 3) {
		fprintf (stderr, "usage: %s <N> <M>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);
	int M = atoi (argv[2]);

	if (N < 3 || M < 2)
		return 1;

	long sum = 0;

	bool * sieve = eratosthenes_sieve (N);
	int * totients = get_totients_under (N, sieve);

	for (int i = 2; i < N; i++) {
		totients[i] = totients[totients[i]] + 1;

		if (sieve[i] && totients[i] == M)
			sum += i;
	}

	printf ("%ld\n", sum);

	free (totients);
	free (sieve);

	return 0;
}
