/*
 * Find the number of circular primes below N
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "math_utils.h"

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

	int upper_limit = pow (10, (int) log10 (N) + 1);

	bool * sieve = eratosthenes_sieve (upper_limit);

	int count = 0;

	for (int i = 2; i < N; i++) {
		char digits[20];

		sprintf (digits, "%d", i);

		int all_primes = 1;
		int rotated_num = i;

		do {
			if (!sieve[rotated_num]) {
				all_primes = 0;
				break;
			}

			int leftmost = digits[0];
			int digit_index = 0;

			for (digit_index = 1; digits[digit_index] != '\0'; digit_index++)
				digits[digit_index - 1] = digits[digit_index];

			digits[digit_index - 1] = leftmost;

			rotated_num = atoi (digits);
		} while (rotated_num != i);

		if (all_primes)
			count++;
	}

	free (sieve);

	printf ("%d\n", count);

	return 0;
}
