/*
 * Find the N-th number that is at the same time triangular, pentagonal and hexagonal
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "math_utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1)
		return 1;

	unsigned long tri_num = 0;
	unsigned long pent_num = 0;
	unsigned long hex_num = 0;

	int count = 0;

	while (1) {
		hex_num = next_hexagonal_num ();

		while (pent_num < hex_num)
			pent_num = next_pentagonal_num ();

		while (tri_num < hex_num)
			tri_num = next_triangle_num ();

		if (pent_num == hex_num && tri_num == hex_num)
			count++;

		if (count == N) {
			printf ("%lu\n", hex_num);
			break;
		}
	}

	return 0;
}
