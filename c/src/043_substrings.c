/*
 * Find the sum of all permutations of 0..9 such that each of its substrings of legth 3 beginning at index i, i > 0, is divisible by the i-th prime
 */

#include <stdlib.h>
#include <stdio.h>
#include "math_utils.h"

#define SUBSTR_LEN	3

int main () {
	int primes[] = {-1, 2, 3, 5, 7, 11, 13, 17};

	char digits[] = "0123456789";

	unsigned long sum = 0;

	do {
		int all_divisible = 1;

		for (int i = 1; i <= 7; i++) {
			int substr_val = 0;

			for (int j = 0; j < SUBSTR_LEN; j++) {
				substr_val *= 10;
				substr_val += digits[i + j] - '0';
			}

			if (substr_val % primes[i]) {
				all_divisible = 0;
				break;
			}
		}

		if (all_divisible) {
			printf ("%s\n",digits);
			sum += atol (digits);
		}
	} while (next_permutation (digits));

	printf ("%lu\n", sum);

	return 0;
}
