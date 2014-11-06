/*
 * Find the first odd composite not representable as a sum of a prime and twice a square
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

static int goldbach_represent (int, char *);

int main () {
	int size = 1000;

	while (1) {
		char * sieve = eratosthenes_sieve (size);

		for (int i = 9; i < size; i += 2) {
			if (sieve[i])
				continue;

			if (!goldbach_represent (i, sieve)) {
				printf ("%d\n", i);
				return 0;
			}
		}

		free (sieve);
		size *= 10;
	}

	return 0;
}

static int goldbach_represent (int num, char * primes) {
	for (int i = 2; i < num; i++) {
		if (!primes[i])
			continue;

		int j = 1;

		while (1) {
			int value = i + 2 * j * j;

			if (value == num)
				return 1;
			else if (value > num)
				break;
			else
				j++;
		}
	}

	return 0;
}
