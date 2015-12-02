/*
 * Find the sum of all n, 0 < n < N, such that the sum of the squares of divisors of n
 * is a perfect square
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"
#include "utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 1)
		return 1;

	long * sums = allocate_array (N, 1L);

	for (long i = 2; i < N; i++) {
		long square = i * i;

		for (int j = i; j < N; j += i)
			sums[j] += square;
	}

	long perfect_squares = 0;

	for (int i = 1; i < N; i++)
		if (integer_sqrt (sums[i]) != -1)
			perfect_squares += i;

	printf ("%ld\n", perfect_squares);

	free (sums);

	return 0;
}
