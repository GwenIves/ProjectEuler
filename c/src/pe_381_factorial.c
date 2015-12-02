/*
 * Let S(p), p prime, be the sum of (p - k)! for 1 <= k <= 5
 * Find the sum of S(p) for 5 <= p < N
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 6)
		return 1;

	bool * sieve = eratosthenes_sieve (N);

	long sum = 0;

	/*
	 * S(p) = (p - 1)! + (p - 2)! + (p - 3)! + (p - 4)! + (p - 5)!
	 *      = (p - 1)! * (1 - 1 + 1 / 2 - 1 / 6 + 1 / 24) (mod p)
	 *      = (p - 1)! * 3 / 8 (mod p)
	 *
	 * By Wilson's theorem, for all primes n, (n - 1)! = (n - 1) mod n
	 *
	 * Then, S(p) = -3/8 (mod p)
	 */

	for (int i = 5; i < N; i++) {
		if (!sieve[i])
			continue;

		sum += i - (3 * modinv (8, i)) % i;
	}

	printf ("%ld\n", sum);

	free (sieve);

	return 0;
}
