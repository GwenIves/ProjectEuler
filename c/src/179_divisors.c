/*
 * Find how many integers n, 1 < n < N have the same number of positive divisors as n + 1
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

// FIXME: This solution is rather slow. No obvious areas for improvement though

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 3)
		return 1;

	int * divisor_counts = allocate_array (N + 1, 2);

	for (int i = 2; i <= N / 2; i++)
		for (int j = i + i; j <= N; j += i)
			divisor_counts[j] += 1;

	int count = 0;

	for (int i = 2; i < N; i++)
		if (divisor_counts[i] == divisor_counts[i + 1])
			count++;

	printf ("%d\n", count);

	free (divisor_counts);

	return 0;
}
