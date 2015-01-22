/*
 * Find how many composites below N have precisely two prime factors
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

static int find_largest_prime (const int *, size_t, size_t, int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 4) {
		printf ("0\n");
		return 0;
	}

	int max_factor = (N - 1) / 2;

	size_t primes_count = 0;
	int * primes = primes_under (NULL, max_factor + 1, &primes_count);

	int count = 0;

	for (size_t i = 0; i < primes_count; i++) {
		int largest_factor = (N - 1) / primes[i];

		if (largest_factor < primes[i])
			break;

		size_t pi = find_largest_prime (primes, i, primes_count - 1, largest_factor);

		count += pi - i + 1;
	}

	printf ("%d\n", count);

	free (primes);

	return 0;
}

// Binary search for the largest prime <= max in the sorted array of primes between from and to
static int find_largest_prime (const int * primes, size_t from, size_t to, int max) {
	while (from < to) {
		size_t middle = (from + to) / 2;

		if (primes[middle] <= max) {
			if (primes[middle + 1] > max)
				return middle;
			else
				from = middle + 1;
		} else
			to = middle - 1;
	}

	return from;
}
