/*
 * Find the sum of all truncatable primes
 */

#include <stdlib.h>
#include <stdio.h>
#include "math_utils.h"

#define KNOWN_COUNT	11

int main () {
	size_t limit = 1000;
	int count = 0;
	unsigned long sum = 0;

	int prime = 11;

	while (true) {
		bool * sieve = eratosthenes_sieve (limit);

		while (prime < limit) {
			bool all_primes = true;
			int num = prime;

			while (num > 0) {
				if (!sieve[num]) {
					all_primes = false;
					break;
				}

				num /= 10;
			}

			if (!all_primes) {
				prime += 2;
				continue;
			}

			char digits[20];

			sprintf (digits, "%d", prime);

			for (int j = 1; digits[j] != '\0'; j++)
				if (!sieve[atoi (digits + j)]) {
					all_primes = false;
					break;
				}

			if (all_primes) {
				sum += prime;

				if (++count == KNOWN_COUNT) {
					printf ("%lu\n", sum);

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
