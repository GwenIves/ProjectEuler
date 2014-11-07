/*
 * Find the first odd composite not representable as a sum of a prime and twice a square
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "math_utils.h"

static int goldbach_represent (int, bool *);

int main () {
	size_t size = 1000;

	while (1) {
		bool * sieve = eratosthenes_sieve (size);

		for (size_t i = 9; i < size; i += 2) {
			if (sieve[i])
				continue;

			if (!goldbach_represent (i, sieve)) {
				printf ("%d\n", (int) i);

				free (sieve);
				return 0;
			}
		}

		free (sieve);
		size *= 10;
	}

	return 0;
}

static int goldbach_represent (int num, bool * primes) {
	for (int i = 2; i < num; i++) {
		if (!primes[i])
			continue;

		int root = sqrt ((num - i) / 2);

		if (num == i + 2 * root * root)
			return 1;
	}

	return 0;
}
