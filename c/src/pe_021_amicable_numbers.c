/*
 * Find the sum of all amicable numbers under N
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

	if (N <= 0)
		return 1;

	long divisors_sums[N];

	for (long i = 1; i < N; i++)
		divisors_sums[i] = proper_divisors_sum (i);

	long amicable_sum = 0;

	for (long i = 1; i < N; i++) {
		long pair = 0;

		if (i == divisors_sums[i])
			continue;

		if (divisors_sums[i] < N)
			pair = divisors_sums[divisors_sums[i]];
		else
			pair = proper_divisors_sum (divisors_sums[i]);

		if (i == pair)
			amicable_sum += i;
	}

	printf ("%ld\n", amicable_sum);

	return 0;
}
