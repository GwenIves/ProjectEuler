/*
 * Find how many square laminae can be formed using up to N tiles
 */

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 0)
		return 1;

	int count = 0;

	for (int inner_size = 3;; inner_size++) {
		int outer_size = 0;
		int squares_used = 0;

		for (outer_size = inner_size;; outer_size += 2) {
			squares_used += (outer_size - 1) * 4;

			if (squares_used > N)
				break;

			count++;
		}

		if (inner_size == outer_size)
			break;
	}

	printf ("%d\n", count);

	return 0;
}
