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

	int size = prime_count_inverse (N);

	int prime = 3;
	int prime_count = 1;

	while (true) {
		bool * sieve = eratosthenes_sieve (size);

		while (prime < size) {
			if (sieve[prime] && ++prime_count == N) {
				printf ("%d\n", prime);

				free (sieve);
				return 0;
			}

			prime += 2;
		}

		free (sieve);
		size *= 2;
	}

	return 0;
}
