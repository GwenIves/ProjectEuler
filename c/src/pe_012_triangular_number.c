/*
 * Find the smallest triangular number with more than N divisors
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	long N = atol (argv[1]);

	if (N < 0)
		return 1;

	while (true) {
		long triangle_num = next_triangle_num ();

		if (divisors_count (triangle_num) > N) {
			printf ("%ld\n", triangle_num);
			return 0;
		}
	}

	return 0;
}
