/*
 * Find the prime below N that is equal to the sum of the largest number of consecutive primes
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

static int sum_primes (bool *, int, int, int);

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

		int count_attempt = max_count + 1;

		while (true) {
			int sum = sum_primes (primes, count_attempt, i, N);

			if (sum < 0)
				break;
			else if (sum >= N)
				break;
			else if (primes[sum]) {
				max_sum = sum;
				max_count = count_attempt;
			}

			count_attempt++;
		}
	}

	printf ("%d\n", max_sum);

	free (primes);

	return 0;
}

static int sum_primes (bool * primes, int count, int first, int under) {
	int next_prime = first;
	int sum = 0;

	for (int i = 0; i < count; i++) {
		sum += next_prime;

		while (next_prime < under)
			if (primes[next_prime += 1])
				break;

		if (next_prime >= under)
			return -1;
	}

	return sum;
}
