/*
 * Find the largest prime factor of N
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	long N = ABS (atol (argv[1]));

	if (N <= 1) {
		printf ("0\n");
		return 0;
	}

	factors_t * factors = factorise (N);

	printf ("%lu\n", factors->factor);

	while (factors) {
		factors_t * t = factors->next;
		free (factors);
		factors = t;
	}

	return 0;
}
