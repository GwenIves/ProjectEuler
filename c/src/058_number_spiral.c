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

	size_t size = 1000;

	while (true) {
		bool * primes = eratosthenes_sieve (size);

		do {
			unsigned int br_corner = side * side;
			unsigned int bl_corner = br_corner - side + 1;
			unsigned int tl_corner = bl_corner - side + 1;
			unsigned int tr_corner = tl_corner - side + 1;

			if (is_prime (primes, bl_corner))
				primes_count++;

			if (is_prime (primes, tl_corner))
				primes_count++;

			if (is_prime (primes, tr_corner))
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
