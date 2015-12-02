/*
 * Find the lowest n such that the equation 1/x + 1/y = 1/n
 * has more than N solutions among positive integers
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"
#include "euler_utils.h"

static int count_divisors_of_a_square (const int *, int);
static int next_prime_to_raise (const int *, int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	/*
	 * 1/x + 1/y = 1/n
	 * xy -nx -ny = 0
	 * xy -nx -ny + n^2 = n^2
	 * (x - n) * (y - n) = n^2
	 *
	 * As x, y, n are integral, x - n must be a divisor of n^2
	 * and y - n a quotient of that division
	 *
	 * We are therefore looking for the lowest n for which
	 * n^2 has more than N (divisor, quotient) pairs
	 *
	 * We will first find an upper bound of n - a product of the lowest number of the first, consecutive primes
	 * that passes the divisor criterion
	 *
	 * This factorisation can be improved by removing a large prime factor and increasing the power of
	 * some smaller prime to re-raise the divisor count as needed
	 * If we list the exponents of the primes in the factorisations (primes in an increasing order),
	 * the powers will obviously form a non-increasing sequence for the smallest n
	 * (because the divisors count formula is independent of prime values, only exponents matter)
	 *
	 * To solve this problem then, we need to search all non-decreasing power sequences under the
	 * upper bound and select the smallest value passing the divisor criterion
	 *
	 * Note: see the implementation of divisors_count () in math_utils.c for details on the logic inlined
	 * in this problem for the special case of divisors of a square
	 */

	long n = 1;
	int divisors_of_n2 = 1;
	int primes_count = 0;

	bool * sieve = eratosthenes_sieve (PRIMES_PRODUCT_LIMIT);

	for (int i = 0;; i++) {
		if (!sieve[i])
			continue;

		primes_count++;
		n *= i;
		divisors_of_n2 *= 3;

		if ((divisors_of_n2 + 1) / 2 > N)
			break;
	}

	int primes[primes_count];
	int powers[primes_count];

	for (int i = 0, j = 0; j < primes_count; i++)
		if (sieve[i])
			primes[j++] = i;

	free (sieve);

	for (int largest_prime = primes_count - 1; largest_prime >= 0; largest_prime--) {
		powers[largest_prime] = 0;

		for (int i = 0; i < largest_prime; i++)
			powers[i] = 1;

		int next_prime = 0;

		do {
			while (true) {
				long val = evaluate_factorisation (primes, powers, primes_count);
				int divisors = count_divisors_of_a_square (powers, primes_count);

				if (val < n && (divisors + 1) / 2 <= N)
					powers[0] += 1;
				else {
					if (val < n)
						n = val;

					break;
				}
			}

			next_prime = next_prime_to_raise (powers, largest_prime);

			if (next_prime > 0) {
				powers[next_prime] += 1;

				for (int j = next_prime - 1; j >= 0; j--)
					powers[j] = powers[next_prime];
			}
		} while (next_prime > 0);
	}

	printf ("%ld\n", n);

	return 0;
}

static int count_divisors_of_a_square (const int * powers, int primes_count) {
	int count = 1;

	for (int i = 0; i < primes_count; i++)
		count *= 2 * powers[i] + 1;

	return count;
}

static int next_prime_to_raise (const int * powers, int largest_prime) {
	for (int i = 1; i < largest_prime; i++)
		/*
		 * Test failed on a power of some prime, it makes no sense to increase the power of a larger prime and retest
		 * if it was only 1 less, the divisor count wouldn't change and the value would increase
		 * The smallest sensible difference is 2
		 */
		if (powers[i] + 2 <= powers[i - 1])
			return i;

	return -1;
}
