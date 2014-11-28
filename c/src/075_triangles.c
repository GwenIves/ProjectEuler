/*
 * Find for how many perimeters less than or equal to N there exists exactly one right sided triangle with integral sides
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "euler_utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 3)
		return 1;

	int * counts = allocate_array (N + 1, 0);

	for (int n = 1;; n++) {
		if (euclid_pythagorean_triple_perim (n + 1, n) > N)
			break;

		for (int m = n + 1;; m++) {
			int primitive_length = euclid_pythagorean_triple_perim (m, n);

			if (primitive_length == 0)
				continue;
			else if (primitive_length > N)
				break;

			for (int len = primitive_length; len <= N; len += primitive_length)
				counts[len] += 1;
		}
	}


	int singular_count = 0;

	for (int i = 0; i <= N; i++)
		if (counts[i] == 1)
			singular_count++;

	printf ("%d\n", singular_count);

	free (counts);

	return 0;
}
