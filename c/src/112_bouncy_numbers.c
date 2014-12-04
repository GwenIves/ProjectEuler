/*
 * Find the smallest number for which there exist exactly N percent bouncy numbers below it
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "math_utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 0 || N > 99)
		return 1;

	int bouncy_count = 0;

	for (int i = 1; i < INT_MAX / 100; i++) {
		if (is_bouncy (i))
			bouncy_count++;

		if (bouncy_count * 100 == i * N) {
			printf ("%d\n", i);
			return 0;
		}
	}

	return 1;
}
