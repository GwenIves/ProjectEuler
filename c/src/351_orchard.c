/*
 * Consider a hexagonal orchard made of points within a regular hexagon of an order N
 * (ie. the hexagon has a side of length N + 1)
 * Find how many points are not visible from the center
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

	if (N < 0)
		return 1;
	/*
	 * The orchard is symetric, each of the 6 parts is composed of lines
	 * of length 1 to N
	 * On a line x, the points will be "visible" from the origin under angles
	 * 60 degrees times 0, 1/x, 2/x, ... 1
	 * Should the fraction be cancellable for point p, then there is a point q
	 * closer to the origin under the same angle and p will be hidden from view
	 * Then, on each line of length x, there will be Totient (x) visible points
	 */

	long hidden = 6 * (arithmetic_sequence_sum (1, N + 1, 1) - totient_sum (N));

	printf ("%ld\n", hidden);

	return 0;
}
