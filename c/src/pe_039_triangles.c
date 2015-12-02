/*
 * Find the perimeter less than or equal to N for which there exists the largest number of right angled triangles with integral length sides and a perimeter equal to it
 */

#include <stdio.h>
#include <stdlib.h>
#include "euler_utils.h"
#include "utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 6)
		return 1;

	int counts[N + 1];

	for (size_t i = 0; i < array_len (counts); i++)
		counts[i] = 0;

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


	int max_count = 0;
	int perimeter_when_max = 0;

	for (size_t i = 0; i < array_len (counts); i++)
		if (counts[i] > max_count) {
			max_count = counts[i];
			perimeter_when_max = i;
		}

	if (max_count > 0) {
		printf ("%d\n", perimeter_when_max);
		return 0;
	} else
		return 1;
}
