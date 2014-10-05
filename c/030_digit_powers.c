/*
 * Find the sum of all the numbers that are equal to the sum of the N-th powers of their digits
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	int digit_powers[10];

	for (int i = 0; i < 10; i++)
		digit_powers[i] = pow (i, N);

	// Find the smallest power of 10 that certainly cannot be represented as a sum of its digit's powers
	int upper_limit = 1;
	int max_representable = digit_powers[9];

	while (upper_limit < max_representable) {
		upper_limit *= 10;
		max_representable += digit_powers[9];
	}

	int sum = 0;

	for (int i = 10; i < upper_limit; i++) {
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
