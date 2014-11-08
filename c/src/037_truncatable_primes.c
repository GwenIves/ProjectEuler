/*
 * Find the sum of all truncatable primes
 */

#include <stdlib.h>
#include <stdio.h>
#include "math_utils.h"

#define KNOWN_COUNT	11

int main () {
	int limit = 1000;

	while (true) {
		bool * sieve = eratosthenes_sieve (limit);

		unsigned long sum = 0;
		int count = 0;

		for (int i = 10; i < limit; i++) {
			int all_primes = 1;
			int num = i;

			while (num > 0) {
				if (!sieve[num]) {
					all_primes = 0;
					break;
				}

				num /= 10;
			}

			if (!all_primes)
				continue;

			char digits[20];

			sprintf (digits, "%d", i);

			for (int j = 1; digits[j] != '\0'; j++)
				if (!sieve[atoi (digits + j)]) {
					all_primes = 0;
					break;
				}

			if (all_primes) {
				sum += i;

				if (++count == KNOWN_COUNT) {
					printf ("%lu\n", sum);

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
