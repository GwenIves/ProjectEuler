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
	else if (N == 1) {
		printf ("2\n");
		return 0;
	}

	size_t size = prime_count_inverse (N);

	while (true) {
		bool * sieve = eratosthenes_sieve (size);

		int prime_count = 1;

		for (size_t i = 3; i < size; i += 2) {
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
