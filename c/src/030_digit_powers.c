/*
 * Find the sum of all the numbers, excluding 1, that are equal to the sum of the N-th powers of their digits
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

	if (N < 0) {
		printf ("0\n");
		return 0;
	}

	int digit_powers[DIGITS_COUNT];

	for (int i = 0; i < DIGITS_COUNT; i++)
		digit_powers[i] = pow (i, N);

	int lowest_pow10 = 1;
	int max_representable = digit_powers[DIGITS_COUNT - 1];

	while (lowest_pow10 < max_representable) {
		lowest_pow10 *= 10;
		max_representable += digit_powers[DIGITS_COUNT - 1];
	}

	int sum = 0;

	for (int i = 10; i <= max_representable; i++) {
		int digit_sum = 0;
		int num = i;

		while (num > 0) {
			int digit = num % 10;
			num /= 10;

			digit_sum += digit_powers[digit];
		}

		if (i == digit_sum)
			sum += i;
	}

	printf ("%d\n", sum);

	return 0;
}
