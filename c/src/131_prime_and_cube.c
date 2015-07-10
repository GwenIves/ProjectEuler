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
	 * The upper limit for the search will be given by consecutive cubes that are N or more units apart:
	 * (a + 1)^3 - a^3 = 3a^2 + 3a + a < N => limit will surely be under sqrt (N / 3)
	 */

	int limit = sqrt (N / 3);

	int cubes[limit + 1];

	for (int i = 0; i <= limit; i++)
		cubes[i] = i * i * i;

	bool * sieve = eratosthenes_sieve (N);

	int count = 0;

	for (int i = 0; i <= limit; i++)
		for (int j = i + 1; j <= limit; j++) {
			int diff = cubes[j] - cubes[i];

			if (diff >= N)
				break;
			else if (sieve[diff])
				count++;
		}

	printf ("%d\n", count);

	free (sieve);

	return 0;
}
