/*
 * Find the sum of all permutations of 0..9 such that each of its substrings of legth 3 beginning at index i, i > 0, is divisible by the i-th prime
 */

#include <stdlib.h>
#include <stdio.h>
#include "math_utils.h"
#include "utils.h"

#define SUBSTR_LEN	3

int main (void) {
	int primes[] = {-1, 2, 3, 5, 7, 11, 13, 17};

	char digits[] = "0123456789";

	long sum = 0;

	do {
		bool all_divisible = true;

		for (size_t i = 1; i < array_len (digits) - SUBSTR_LEN; i++) {
			int substr_val = 0;

			for (size_t j = 0; j < SUBSTR_LEN; j++) {
				substr_val *= 10;
				substr_val += digits[i + j] - '0';
			}

			if (substr_val % primes[i]) {
				all_divisible = false;
				break;
			}
		}

		if (all_divisible)
			sum += atol (digits);
	} while (next_permutation (digits));

	printf ("%ld\n", sum);

	return 0;
}
