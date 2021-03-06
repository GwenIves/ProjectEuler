/*
 * Find the side length of a number spiral constructed from 1 moving right and then counter-clockwise,
 * such that the ratio of primes to all numbers on the diagonals falls below N %
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "math_utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 0 || (N > 100))
		return 1;

	int side = 3;
	int numbers_count = 5;
	int primes_count = 0;

	int size = 1000;

	while (true) {
		bool * primes = eratosthenes_sieve (size);

		do {
			int br_corner = side * side;
			int bl_corner = br_corner - side + 1;
			int tl_corner = bl_corner - side + 1;
			int tr_corner = tl_corner - side + 1;

			if (is_prime (bl_corner, primes, size))
				primes_count++;

			if (is_prime (tl_corner, primes, size))
				primes_count++;

			if (is_prime (tr_corner, primes, size))
				primes_count++;

			if (primes_count * 100.0 / numbers_count < N) {
				printf ("%d\n", side);

				free (primes);
				return 0;
			}

			side += 2;
			numbers_count += 4;
		} while (side < size);

		free (primes);
		size *= 10;
	}

	return 0;
}
