/*
 * Find the smallest triangular number with more than N divisors
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

	int N = atoi (argv[1]);

	while (1) {
		unsigned long triangle_num = next_triangle_num ();
		int divisors = 0;

		unsigned long upper_limit = sqrt (triangle_num);
		for (unsigned long i = 1; i <= upper_limit; i++)
			if (triangle_num % i == 0) {
				if (i * i == triangle_num)
					divisors++;
				else
					divisors += 2;
			}

		if (divisors > N) {
			printf ("%lu\n", triangle_num);
			return 0;
		}
	}

	return 0;
}
