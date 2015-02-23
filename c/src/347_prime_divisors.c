/*
 * Let M(p,q,n) be the largest integer x <= n divisible by only primes p and q, p != q
 * Find the sum of all M(p,q,N)
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

static long get_largest_product (long, long, long);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	long N = atol (argv[1]);

	if (N < 6) {
		printf ("0\n");
		return 0;
	}

	long sum = 0;

	long limit = N / 2;
	bool * sieve = eratosthenes_sieve (limit + 1);

	for (long i = 2; i <= limit; i++) {
		if (!sieve[i])
			continue;

		for (long j = i + 1; j <= limit; j++) {
			if (!sieve[j])
				continue;

			if (i * j > N)
				break;

			sum += get_largest_product (i, j, N);
		}
	}

	printf ("%ld\n", sum);

	free (sieve);

	return 0;
}

static long get_largest_product (long p, long q, long N) {
	long largest = 0;

	for (long product_p = p;; product_p *= p) {
		long product = product_p * q;

		if (product > N)
			return largest;

		while (product * q <= N)
			product *= q;

		if (product > largest)
			largest = product;
	}
}
