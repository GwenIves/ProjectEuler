/*
 * Find the first odd composite not representable as a sum of a prime and twice a square
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "math_utils.h"

static bool goldbach_represent (int, bool *);

int main () {
	size_t size = 1000;

	int candidate = 9;

	while (true) {
		bool * sieve = eratosthenes_sieve (size);

		while (candidate < size) {
			if (!sieve[candidate] && !goldbach_represent (candidate, sieve)) {
				printf ("%d\n", candidate);

				free (sieve);
				return 0;
			}

			candidate += 2;
		}

		free (sieve);
		size *= 10;
	}

	return 0;
}

static bool goldbach_represent (int num, bool * primes) {
	for (int i = 2; i < num; i++) {
		if (!primes[i])
			continue;

		int root = sqrt ((num - i) / 2);

		if (num == i + 2 * root * root)
			return true;
	}

	return false;
}
