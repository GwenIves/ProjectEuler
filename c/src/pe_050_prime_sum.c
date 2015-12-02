/*
 * Find the prime below N that is equal to the sum of the largest number of consecutive primes
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

static int sum_primes (const bool *, int *, int, int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 3)
		return 1;

	bool * primes = eratosthenes_sieve (N);

	int max_sum = 0;
	int max_count = 0;

	for (int i = 2; i < N; i++) {
		if (!primes[i])
			continue;

		int count = 0;
		int sum = sum_primes (primes, &count, i, N);

		if (count > max_count) {
			max_sum = sum;
			max_count = count;
		}
	}

	printf ("%d\n", max_sum);

	free (primes);

	return 0;
}

static int sum_primes (const bool * primes, int * count, int first, int under) {
	int sum = 0;
	int primes_added = 0;
	int prime = first;

	int max_while_prime = 0;
	int sum_while_prime = 0;

	while (true) {
		sum += prime;

		if (sum >= under) {
			*count = max_while_prime;
			return sum_while_prime;
		} else {
			primes_added++;

			if (primes[sum]) {
				max_while_prime = primes_added;
				sum_while_prime = sum;
			}
		}

		while (prime < under - 1)
			if (primes[prime += 1])
				break;
	}
}
