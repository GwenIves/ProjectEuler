/*
 * Find how many reduced proper fractions a/b exist for b less than or equal to N
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

	// For each denominator, except 1, there is exactly Totient (denominator) reduced proper fractions
	long count = totient_sum (N) - 1;

	printf ("%ld\n", count);

	return 0;
}
