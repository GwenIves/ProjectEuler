/*
 * Consider repunits of length n, R(n), where gcd(n, 10) == 1
 * Let A(n) be the smallest n such that n divides R(n)
 * Find the sum of the first N composites c, such that
 * c - 1 is divisible by A(c)
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"
#include "euler_utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 0)
		return 1;

	long sum = 0;
	int count = 0;

	for (int i = 2; count < N; i++) {
		if (is_prime_long (i, NULL, 0, NULL, 0))
			continue;

		int len = get_repunit_len (i);

		if (len == 0)
			continue;

		if ((i - 1) % len == 0) {
			sum += i;
			count++;
		}
	}

	printf ("%ld\n", sum);

	return 0;
}
