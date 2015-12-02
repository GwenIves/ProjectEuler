/*
 * Find the difference between the sum of the squares of the first N natural numbers and the square of the sum
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

static long get_sum_of_squares (int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1)
		return 1;

	long sum = arithmetic_sequence_sum (1, N + 1, 1);
	long sum_of_squares = get_sum_of_squares (N);

	printf ("%ld\n", sum * sum - sum_of_squares);

	return 0;
}

static long get_sum_of_squares (int up_to) {
	long sum = 0;

	sum = (((2 * up_to + 3) * up_to) + 1) * up_to;
	sum /= 6;

	return sum;
}
