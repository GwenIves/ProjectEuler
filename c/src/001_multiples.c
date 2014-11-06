/*
 * Find the sum of all natural numbers less than N that are multiples of 3 and 5
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

	if (N < 0) {
		printf ("0\n");
		return 0;
	}

	long sum3 = arithmetic_sequence_sum (0, N, 3);
	long sum5 = arithmetic_sequence_sum (0, N, 5);
	long sum15 = arithmetic_sequence_sum (0, N, 15);

	printf ("%ld\n", sum3 + sum5 - sum15);

	return 0;
}
