/*
 * Find the largest concatenation of 3 N-digit numbers that are all primes and permutations of each other
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

	int lower_limit = pow (10, N - 1);
	int upper_limit = lower_limit * 10 - 1;
	long multiplier = lower_limit * 10;

	bool * primes = eratosthenes_sieve (upper_limit);
	char * next_perm = x_malloc (N + 1);

	long max = 0;

	for (int start = lower_limit; start <= upper_limit; start++) {
		if (!primes[start])
			continue;

		sprintf (next_perm, "%d", start);

		while (next_permutation (next_perm)) {
			int next_val = atoi (next_perm);

			if (!primes[next_val])
				continue;

			int final_val = next_val + next_val - start;

			if (final_val > upper_limit)
				continue;

			if (!primes[final_val])
				continue;

			if (!is_permutation (next_val, final_val))
				continue;

			long seq_val = (((start * multiplier) + next_val) * multiplier) + final_val;

			if (seq_val > max)
				max = seq_val;
		}

	}

	printf ("%ld\n", max);

	free (primes);
	free (next_perm);

	return 0;
}
