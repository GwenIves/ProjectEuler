/*
 * Find how many right-angled triangles can be formed with all vertices on integer coordinates between 0 and N inclusive
 * One vertex is fixed at the origin
 */

#include <stdio.h>
#include <stdlib.h>
#include <utils.h>

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 0)
		return 1;

	int count = 0;

	// Encode points (x,y) in a grid of size N x N as integers i = (y * N) + x

	int last_coordinate = (N + 1) * (N + 1) - 1;

	for (int i = 1; i <= last_coordinate; i++) {
		int x1 = i % (N + 1);
		int y1 = i / (N + 1);

		for (int j = i + 1; j <= last_coordinate; j++) {
			int x2 = j % (N + 1);
			int y2 = j / (N + 1);

			int side_squares[3];

			side_squares[0] = x1 * x1 + y1 * y1;
			side_squares[1] = x2 * x2 + y2 * y2;
			side_squares[2] = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);

			qsort (side_squares, 3, sizeof (int), int_cmp);

			if (side_squares[0] + side_squares[1] == side_squares[2])
				count++;
		}
	}

	printf ("%d\n", count);

	return 0;
}
