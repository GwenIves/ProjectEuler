/*
 * Find the N-th prime
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

	size_t size = N * 5;

	while (1) {
		char * sieve = eratosthenes_sieve (size);

		int prime_count = 0;

		for (size_t i = 2; i < size; i++) {
			if (sieve[i] && ++prime_count == N) {
				printf ("%d\n", (int) i);

				free (sieve);
				return 0;
			}
		}

		free (sieve);
		size *= 2;
	}

	return 0;
}
