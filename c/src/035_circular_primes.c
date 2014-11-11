/*
 * Find the number of circular primes below N
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "math_utils.h"

static void rotate (char *);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 2) {
		printf ("0\n");
		return 0;
	}

	int digits_count = log10 (N) + 1;
	int upper_limit = pow (10, digits_count);

	bool * sieve = eratosthenes_sieve (upper_limit);

	int count = 1;

	for (int i = 3; i < N; i += 2) {
		char digits[digits_count + 1];

		if (!sieve[i])
			continue;

		sprintf (digits, "%d", i);

		bool all_primes = true;
		int rotated_num = i;

		do {
			if (!sieve[rotated_num]) {
				all_primes = false;
				break;
			}

			rotate (digits);

			rotated_num = atoi (digits);
		} while (rotated_num != i);

		if (all_primes)
			count++;
	}

	free (sieve);

	printf ("%d\n", count);

	return 0;
}

static void rotate (char * digits) {
	int leftmost = digits[0];
	size_t digit_index = 0;

	for (digit_index = 1; digits[digit_index] != '\0'; digit_index++)
		digits[digit_index - 1] = digits[digit_index];

	digits[digit_index - 1] = leftmost;
}
