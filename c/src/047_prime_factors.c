/*
 * Find the first of N consecutive numbers with N prime factors each
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

	long start = 0;
	int len = 0;
	long i = 2;

	while (true) {
		if (factors_count (i) >= N) {
			if (len++ == 0)
				start = i;

			if (len == N)
				break;
		} else
			len = 0;

		i++;
	}

	printf ("%ld\n", start);

	return 0;
}
