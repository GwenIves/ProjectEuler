/*
 * Let x, y, z be consecutive terms of an arithmetic sequence
 * Find how many n < N give exactly M solutions to the equation
 * x^2 - y^2 - z^2 = n
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main (int argc, char ** argv) {
	if (argc != 3) {
		fprintf (stderr, "usage: %s <M> <N>\n", argv[0]);
		return 1;
	}

	int M = atoi (argv[1]);
	int N = atoi (argv[2]);

	if (M < 1 || N <= 1)
		return 1;

	/*
	 * n = (x + 2k)^2 - (x + k)^2 - x^2
	 * n = -2x^2 + x^2 + 2xk + k^2 + 2k^2
	 * n = (x + k)^2 + 2(k^2 - x^2)
	 * n = (x + k)^2 + 2(k - x)(k + x)
	 * n = (x + k)(x + k + 2k - 2x)
	 * n = (x + k)(3k - x)
	 */

	int * div_counts = allocate_array (N, 0);

	for (int x = 1; x < 3 * N / 4; x++)
		for (int k = x / 3;; k++) {
			long n = (x + k) * (long) (3 * k - x);

			if (n < 0)
				continue;
			else if (n >= N)
				break;

			div_counts[n] += 1;
		}

	int count = 0;

	for (int i = 0; i < N; i++)
		if (div_counts[i] == M)
			count++;

	printf ("%d\n", count);

	free (div_counts);

	return 0;
}
