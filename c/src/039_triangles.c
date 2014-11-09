/*
 * Find the perimeter less than or equal to N for which there exists the largest number of right sided triangles with integral length sides and a perimeter equal to it
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 3)
		return 1;

	int max = 0;
	int max_count = 0;

	// Precompute squares used in the calculation
	int squares[N - 1];

	for (int i = 0; i < array_len (squares); i++)
		squares[i] = i * i;

	for (int n = 3; n <= N; n++) {
		int triangles = 0;

		for (int a = 1; a < n - 1; a++)
			for (int b = a; b < n - 1; b++) {
				int c = n - a - b;

				if (b > a + c)
					break;

				if (squares[a] + squares[b] == squares[c])
					triangles++;
			}

		if (triangles > max_count) {
			max_count = triangles;
			max = n;
		}
	}

	if (max_count > 0) {
		printf ("%d\n", max);
		return 0;
	} else
		return 1;
}
