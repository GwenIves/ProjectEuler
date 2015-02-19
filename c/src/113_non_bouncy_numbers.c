/*
 * Find how many numbers below 10^N are non-bouncy
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 0)
		return 1;
	else if (N == 0) {
		printf ("1\n");
		return 0;
	}

	/*
	 * The arrays hold at index i,j the number of (non-strictly) increasing/decreasing integers
	 * of (i + 1) digits ending with j
	 */
	long increasing_counts[N][DIGITS_COUNT];
	long decreasing_counts[N][DIGITS_COUNT];

	long total = 9;

	for (size_t i = 0; i < DIGITS_COUNT; i++) {
		increasing_counts[0][i] = 1;
		decreasing_counts[0][i] = 1;
	}

	for (int digit = 1; digit < N; digit++) {
		for (int value = 0; value < DIGITS_COUNT; value++) {
			increasing_counts[digit][value] = 0;
			decreasing_counts[digit][value] = 0;

			for (int i = value; i >= 0; i--)
				increasing_counts[digit][value] += increasing_counts[digit - 1][i];

			for (int i = value; i < DIGITS_COUNT; i++)
				decreasing_counts[digit][value] += decreasing_counts[digit - 1][i];

			// Disregard leading zeros
			if (value > 0) {
				total += increasing_counts[digit][value];
				total += decreasing_counts[digit][value];

				// Compensation for double-counted integers
				// that are both non-increasing and non-decreasing, eg. 333
				total--;
			}
		}
	}

	printf ("%ld\n", total);

	return 0;
}
