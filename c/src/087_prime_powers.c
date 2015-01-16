/*
 * Find how many numbers below N can be expressed as a sum of a prime square, cube and fourth power
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include "math_utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1)
		return 1;

	bool * representable = allocate_array (N, (bool) false);

	int limit = sqrt (N) + 1;

	bool * sieve = eratosthenes_sieve (limit);

	for (int a = 2; a < limit; a++) {
		if (!sieve[a])
			continue;

		int a2 = a * a;

		if (a2 >= N)
			break;

		for (int b = 2; b < limit; b++) {
			if (!sieve[b])
				continue;

			int b3 = b * b * b;

			if (a2 + b3 >= N)
				break;

			for (int c = 2; c < limit; c++) {
				if (!sieve[c])
					continue;

				int c4 = c * c * c * c;

				int sum = a2 + b3 + c4;

				if (sum >= N)
					break;
				else
					representable[sum] = true;
			}
		}
	}

	int count = 0;

	for (int i = 0; i < N; i++)
		if (representable[i])
			count++;

	printf ("%d\n", count);

	free (representable);
	free (sieve);

	return 0;
}
