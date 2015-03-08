/*
 * A bag contains M balls for each of the 7 colors of the rainbow
 * Find the expected number of colors in N randomly picked balls
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

#define count_partitions(n,p,l) count_partitions_ (n, p, l, 1)

#define RAINBOW_COLORS	7

static long count_partitions_ (int, int, int, long);

int main (int argc, char ** argv) {
	if (argc != 3) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int M = atoi (argv[1]);
	int N = atoi (argv[2]);

	if (N <= 0 || N > M * RAINBOW_COLORS)
		return 1;

	long colors_count = 0;
	long choices_count = 0;

	for (int colors = 1; colors <= RAINBOW_COLORS; colors++) {
		long possible_choices = count_partitions (N, colors, M) * binomial_coefficient (RAINBOW_COLORS, colors);

		choices_count += possible_choices;
		colors_count += colors * possible_choices;
	}

	printf ("%.9f\n", (double) colors_count / choices_count);

	return 0;
}

static long count_partitions_ (int num, int partitions_number, int limit, long combinations) {
	long count = 0;

	if (num <= 0)
		count = 0;
	else if (partitions_number == 1) {
		if (num <= limit)
			count = combinations * binomial_coefficient (limit, num);
		else
			count = 0;
	} else {
		int max_addition = MIN (num, limit);

		for (int i = 1; i <= max_addition; i++)
			count += count_partitions_ (num - i, partitions_number - 1, limit, combinations * binomial_coefficient (limit, i));
	}

	return count;
}
