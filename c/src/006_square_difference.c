/*
 * Find the difference between the sum of the squares of the first N natural numbers and the square of the sum
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

	if (N < 1)
		return 1;

	unsigned long square_of_sum = arithmetic_sequence_sum (1, N + 1, 1);
	square_of_sum *= square_of_sum;

	unsigned long sum_of_squares = 0;

	for (int i = 1; i <= N; i++)
		sum_of_squares += i * i;

	printf ("%lu\n", square_of_sum - sum_of_squares);

	return 0;
}
