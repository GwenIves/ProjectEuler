/*
 * Find the sum of all truncatable primes
 */

#include <stdlib.h>
#include <stdio.h>
#include "math_utils.h"

#define KNOWN_COUNT	11

static bool is_truncatable (bool *, int);

int main () {
	size_t limit = 1000;
	int count = 0;
	long sum = 0;

	int prime = 11;

	while (true) {
		bool * sieve = eratosthenes_sieve (limit);

		while (prime < limit) {
			if (is_truncatable (sieve, prime)) {
				sum += prime;

				if (++count == KNOWN_COUNT) {
					printf ("%ld\n", sum);

					free (sieve);
					return 0;
				}
			}

			prime += 2;
		}

		free (sieve);
		limit *= 10;
	}

	return 0;
}

static bool is_truncatable (bool * sieve, int prime) {
	int num = prime;

	while (num > 0) {
		if (!sieve[num])
			return false;

		num /= 10;
	}

	char digits[20];

	sprintf (digits, "%d", prime);

	for (size_t j = 1; digits[j] != '\0'; j++)
		if (!sieve[atoi (digits + j)])
			return false;

	return true;
}
