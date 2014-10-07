/*
 * Find the largest prime factor of N
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

	long upper_limit = sqrt (N);
	long factor = 2;
	long max_factor = 1;

	while (N != 1) {
		if (N % factor == 0) {
			max_factor = factor;
				
			while (N % factor == 0)
				N /= factor;

			upper_limit = sqrt (N);
		}

		if (N == 1)
			break;
		else if (++factor > upper_limit) {
			max_factor = N;
			break;
		}
	}

	printf ("%ld\n", max_factor);

	return 0;
}
