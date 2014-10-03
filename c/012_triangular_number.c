/*
 * Find the smallest triangular number with more than N divisors
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static unsigned long next_triangle_num ();

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
				if (i == upper_limit)
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

static unsigned long next_triangle_num () {
	static unsigned long last_natural_num = 0;
	static unsigned long last_triangle_num = 0;

	last_natural_num++;
	last_triangle_num += last_natural_num;

	return last_triangle_num;
}
