/*
 * Find how many tiles (maximum 1 million) can form up to N different square laminae
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#define TILES	1000000

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 0)
		return 1;

	int * laminae_counts = allocate_array (TILES + 1, 0);

	for (int inner_size = 3;; inner_size++) {
		int outer_size = 0;
		int squares_used = 0;

		for (outer_size = inner_size;; outer_size += 2) {
			squares_used += (outer_size - 1) * 4;

			if (squares_used > TILES)
				break;

			laminae_counts[squares_used] += 1;
		}

		if (inner_size == outer_size)
			break;
	}

	int count = 0;

	for (size_t i = 0; i <= TILES; i++)
		if (laminae_counts[i] > 0 && laminae_counts[i] <= N)
			count++;

	printf ("%d\n", count);

	free (laminae_counts);

	return 0;
}
