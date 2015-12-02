/*
 * There are primes p for which there exists a unique integer n, such that
 * n^3 + p * n^2 is a perfect cube
 * Find how many such primes exist below N
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

	if (N < 0)
		return 1;

	/*
	 * n^3 + p * n^2 = n^2 * (n + p)
	 *
	 * For this to be a perfect cube, all prime factors have to exist in sets of three
	 * The only way for this to happen, n^2 has to be a square of a cube and n + p has to be a cube
	 *
	 * Therefore, we are looking for primes p that are equal to a difference between cubes
	 *
	 * Since a^3 - b^3 = (a - b) * (a^2 + ab + b^2), (a - b) has to be 1 in order for the difference
	 * to be prime and we only have to check consecutive cube pairs
	 */

	bool * sieve = eratosthenes_sieve (N);

	int count = 0;
	int prev_cube = 1;

	for (int i = 2;; i++) {
		int cube = i * i * i;

		int diff = cube - prev_cube;
		prev_cube = cube;

		if (diff >= N)
			break;
		else if (sieve[diff])
			count++;
	}

	printf ("%d\n", count);

	free (sieve);

	return 0;
}
