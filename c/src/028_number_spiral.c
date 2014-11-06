/*
 * Find the sum of the numbers on the diagonal of an NxN number spiral constructed from 1 moving right and then clockwise
 */

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1)
		return 1;

	unsigned long sum = 1;

	for (int side = 3; side <= N; side += 2) {
		unsigned long tr_corner = side * side;
		unsigned long tl_corner = tr_corner - side + 1;
		unsigned long bl_corner = tl_corner - side + 1;
		unsigned long br_corner = bl_corner - side + 1;

		sum += tr_corner + tl_corner + bl_corner + br_corner;
	}

	printf ("%lu\n", sum);

	return 0;
}
