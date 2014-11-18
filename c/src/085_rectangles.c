/*
 * Find the area of a rectangle closest to N that contains N sub-rectangles
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

	int smallest_diff = -1;
	int closest_area = 0;

	// Rectangle i*j can contain (1 + 2 + ... + i) * (1 + 2 + ... + j) subrectangles
	for (int i = 1;; i++) {
		int i_sum = arithmetic_sequence_sum (1, i + 1, 1);

		for (int j = 1;; j++) {
			int j_sum = arithmetic_sequence_sum (1, j + 1, 1);

			int subrectangles = i_sum * j_sum;
			int diff = ABS (subrectangles - N);

			if (smallest_diff == -1 || diff < smallest_diff) {
				smallest_diff = diff;
				closest_area = i * j;
			}

			if (subrectangles > N)
				break;
		}

		if (i_sum > N)
			break;
	}

	printf ("%d\n", closest_area);

	return 0;
}
