/*
 * Find the smallest x + y + z, x > y > z > 0 such that:
 * x + y, x − y, x + z, x − z, y + z, y − z are all perfect squares.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "math_utils.h"

int main (void) {
	/*
	 * x + y = a^2
	 * x - y = b^2
	 * x + z = c^2
	 * x - z = d^2
	 * y + z = e^2
	 * y - z = f^2
	 *
	 * c < a && a^2 - c^2 = f^2
	 * b < c && c^2 - b^2 = e^2
	 * a + b > c && a^2 + b^2 - c^2 = d^2
	 */

	int limit = 10;
	int min_sum = 0;
	bool exhaustive = false;

	while (true) {
		for (int a = 3; a < limit; a++) {
			int a2 = a * a;

			for (int c = 2; c < a; c++) {
				int c2 = c * c;

				if (integer_sqrt (a2 - c2 /* f^2 */) == -1)
					continue;

				for (int b = 1; b < c; b++) {
					int b2 = b * b;

					if (integer_sqrt (c2 - b2 /* e^2 */) == -1)
						continue;
					else if (integer_sqrt (a2 + b2 - c2 /* d^2 */) == -1)
						continue;

					int x = (a2 + b2) / 2;
					int y = (a2 - b2) / 2;
					int z = c2 - x;

					if (z < 0)
						continue;
					else if (integer_sqrt (x + y /* a^2 */) == -1)
						continue;
					else if (integer_sqrt (x - y /* b^2 */) == -1)
						continue;
					else if (integer_sqrt (x + z /* c^2 */) == -1)
						continue;

					int sum = x + y + z;

					if (min_sum == 0 || sum < min_sum)
						min_sum = sum;
				}
			}
		}

		if (min_sum > 0) {
			if (exhaustive)
				break;
			else {
				/*
				 * Check if there is a lower sum given a higher limit
				 * Because (a2 + b2) / 2 = x < sum => a^2 certainly cannot exceed 2 * sum
				 */
				limit = sqrt (2 * min_sum);
				exhaustive = true;
			}
		} else
			limit *= 10;
	}

	printf ("%d\n", min_sum);

	return 0;
}
