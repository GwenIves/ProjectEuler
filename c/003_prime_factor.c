/*
 * Find the largest prime factor of N
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	unsigned long N = atol (argv[1]);

	unsigned long upper_limit = sqrt (N);
	unsigned long factor = 2;
	unsigned long max_factor = 1;

	while (N != 1) {
		if (N % factor == 0) {
			max_factor = factor;
				
			while (N % factor == 0)
				N /= factor;

			upper_limit = sqrt (N);
		}

		if (++factor > upper_limit) {
			max_factor = N;
			break;
		}
	}

	printf ("%lu\n", max_factor);

	return 0;
}
