/*
 * Find the sum of all amicable numbers under N
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

	int * divisors_sums = x_malloc (N * sizeof (int));

	for (int i = 1; i < N; i++)
		divisors_sums[i] = divisors_sum (i);

	unsigned long amicable_sum = 0;

	for (int i = 1; i < N; i++) {
		int pair = 0;

		if (i == divisors_sums[i])
			continue;

		if (divisors_sums[i] < N)
			pair = divisors_sums[divisors_sums[i]];
		else
			pair = divisors_sum (divisors_sums[i]);

		if (i == pair)
			amicable_sum += i;
	}

	printf ("%lu\n", amicable_sum);

	free (divisors_sums);

	return 0;
}
