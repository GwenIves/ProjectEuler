/*
 * Let R(x) be a repunit of length x
 * Find the sum of the first M primes that divide R(N)
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

int main (int argc, char ** argv) {
	if (argc != 3) {
		fprintf (stderr, "usage: %s <M> <N>\n", argv[0]);
		return 1;
	}

	int M = atoi (argv[1]);
	int N = atoi (argv[2]);

	if (N < 1 || M < 1)
		return 1;

	int sum = 0;
	int count = 0;

	int limit = 10;
	int prime = 3;

	/*
	 * R(n) = (10^n - 1) / 9
	 * If R(n) % p == 0, then (10^n - 1) / 9p == 0
	 * 10^n == 1 (mod 9p)
	 */

	while (true) {
		bool * sieve = eratosthenes_sieve (limit);

		for (; prime < limit; prime += 2) {
			if (!sieve[prime])
				continue;

			if (mod_pow (10, N, 9 * prime) == 1) {
				sum += prime;

				if (++count >= M) {
					printf ("%d\n", sum);

					free (sieve);
					return 0;
				}
			}
		}

		free (sieve);
		limit *= 10;
	}

	return 0;
}
