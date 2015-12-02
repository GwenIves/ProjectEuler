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

	if (N < 1 || (N % 2 == 0))
		return 1;

	long sum = 1;

	for (int side = 3; side <= N; side += 2) {
		long tr_corner = side * side;
		long tl_corner = tr_corner - side + 1;
		long bl_corner = tl_corner - side + 1;
		long br_corner = bl_corner - side + 1;

		sum += tr_corner + tl_corner + bl_corner + br_corner;
	}

	printf ("%ld\n", sum);

	return 0;
}
