/*
 * Two discs are being drawn from a box containing blue and and red discs
 * Find how many blue discs must be contained in the smallest box with over N discs
 * such that the probability of drawing two blue discs out of it is exactly 50%
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	long N = atol (argv[1]);

	/*
	 * b == blue discs count, t == total discs count
	 * b / t * (b - 1) / (t - 1) = 1 / 2
	 *
	 * b, t are integral, we will solve the Diophantine equation by transforming
	 * it to a negative Pell equation first
	 *
	 * 2b (b - 1) - t (t - 1) = 0
	 * 2 (b^2 - b) - (t^2 - t) = 0
	 * 2 (b - 1/2)^2 - 1/2 - (t - 1/2)^2 + 1/4 = 0
	 * 2 (2b - 1)^2 - (2t - 1)^2 = 1
	 *
	 * Now substitute x = 2t - 1, y = 2b - 1
	 * x^2 - 2y^2 = -1
	 *
	 * We have a negative Pell equation with D == 2
	 * The fundamental solution will be the first convergent of sqrt (D)
	 * that satisfies the equation. For D == 2, it is x == y == 1
	 *
	 * Additional solutions are given by the recurrence equations.
	 * Not all results of the recurrences will satisfy the negative equation
	 * so we have to test them
	 */

	long x = 1;
	long y = 1;

	while (true) {
		long new_x = x + 2 * y;
		long new_y = y + x;

		if (new_x * new_x - 2 * new_y * new_y == -1) {
			long total = (new_x + 1) / 2;
			long blue = (new_y + 1) / 2;

			if (total > N) {
				printf ("%ld\n", blue);
				break;
			}
		}

		x = new_x;
		y = new_y;
	}

	return 0;
}
