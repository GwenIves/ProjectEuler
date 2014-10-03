/*
 * Find the sum of all amicable numbers under N
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"

static int divisor_sum (int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	int * divisor_sums = x_malloc (N * sizeof (int));

	for (int i = 1; i < N; i++)
		divisor_sums[i] = divisor_sum (i);

	unsigned long amicable_sum = 0;

	for (int i = 1; i < N; i++) {
		int pair = 0;

		if (i == divisor_sums[i])
			continue;

		if (divisor_sums[i] < N)
			pair = divisor_sums[divisor_sums[i]];
		else
			pair = divisor_sum (divisor_sums[i]);

		if (i == pair)
			amicable_sum += i;
	}

	printf ("%lu\n", amicable_sum);

	free (divisor_sums);

	return 0;
}

static int divisor_sum (int num) {
	int sum = 1;

	int upper_limit = sqrt (num);

	for (int i = 2; i <= upper_limit; i++)
		if (num % i == 0) {
			int div = num / i;

			if (i == div)
				sum += i;
			else
				sum += i + div;
		}

	return sum;
}
