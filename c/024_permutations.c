/*
 * Find the N-th permutation of the digits 0..9, lexicographically ordered
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

	char sequence[11] = "0123456789";

	do {
		N--;

		if (N <= 0) {
			printf ("%s\n", sequence);
			break;
		}
	} while (next_permutation (sequence));

	return 0;
}
