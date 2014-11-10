/*
 * Find the smallest positive integer the 1st to N-th multiple of which are all its permutations
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

	int number = 1;

	while (true) {
		int multiple = 1;

		while (multiple <= N) {
			if (!is_permutation (number, number * multiple))
				break;

			multiple++;
		}

		if (multiple > N)
			break;

		number++;
	}

	printf ("%d\n", number);

	return 0;
}
