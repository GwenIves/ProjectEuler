/*
 * Find the sum of the legs of the N smallest isosceles triangles for which height = base +/- 1
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

static long get_leg (int, int);
static int get_m (long, long, long);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 0)
		return 1;

	long sum = 0;
	int count = 0;

	/*
	 * See comments in problem 94 for explanation of the algorithm
	 * This problem is principally the same, only the equations have changed
	 */

	for (int n = 1;; n++) {
		long n2 = (long) n * n;
		long m = 0;

		if ((m = get_m (1, -4 * n, -n2 + 1)) == -1)
			m = get_m (1, -4 * n, -n2 - 1);
		if (m < 0 && (m = get_m (-2, 2 * n, 2 * n2 + 1)) == -1)
			m = get_m (-2, 2 * n, 2 * n2 - 1);

		if (m > 0) {
			long leg = get_leg (m, n);

			if (leg > 0) {
				sum += leg;

				if (++count >= N)
					break;
			}
		}
	}

	printf ("%ld\n", sum);

	return 0;
}

// The hypotenuse of the generating right-angled triangle will be the leg
static long get_leg (int m, int n) {
	long sides[3];

	if (!euclid_pythagorean_triple (m, n, sides, sides + 1, sides + 2))
		return 0;

	return sides[2];
}

static int get_m (long a, long b, long c) {
	long x1 = 0;
	long x2 = 0;

	if (integer_solve_quadratic (a, b, c, &x1, &x2))
		return x2;
	else
		return -1;
}
