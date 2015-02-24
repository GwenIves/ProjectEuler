/*
 * Find the sum of all distinct pseudo-fortunate numbers for admissible numbers under N
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"
#include "euler_utils.h"
#include "linked_list.h"
#include "utils.h"

static size_t count_primes (const bool *, int);
static void fill_factor_arrays (int *, int *, const bool *, size_t);
static int find_pseudo_fortunate (int);
static int next_prime (const int *, int *, size_t, int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	bool * sieve = eratosthenes_sieve (PRIMES_PRODUCT_LIMIT);

	size_t primes_count = count_primes (sieve, N);

	if (primes_count == 0) {
		printf ("0\n");
		return 0;
	}

	int primes[primes_count];
	int powers[primes_count];

	fill_factor_arrays (primes, powers, sieve, primes_count);

	free (sieve);

	linked_list_t * pseudo_fortunates = linked_list_create ();

	int prime = 0;

	while ((prime = next_prime (primes, powers, primes_count, N)) > 0) {
		int val = find_pseudo_fortunate (prime);

		linked_list_add_sorted (pseudo_fortunates, copy_int (val), int_cmp, true);
	}

	int sum = linked_list_sum_int (pseudo_fortunates);

	printf ("%d\n", sum);

	linked_list_free (pseudo_fortunates);

	return 0;
}

static int next_prime (const int * primes, int * powers, size_t count, int limit) {
	static size_t start = 0;

	while (start < count) {
		powers[start] += 1;

		long prime = evaluate_factorisation (primes, powers, count);

		if (prime < limit) {
			start = 0;
			return prime;
		} else {
			for (size_t i = 0; i <= start; i++)
				powers[i] = 1;

			start++;
		}
	}

	return 0;
}

static int find_pseudo_fortunate (int admissible) {
	int fortunate = 2;

	while (!is_prime_long (admissible + fortunate, NULL, 0, NULL, 0))
		fortunate++;

	return fortunate;
}

static size_t count_primes (const bool * sieve, int limit) {
	size_t count = 0;
	long product = 1;

	for (int i = 2; i < PRIMES_PRODUCT_LIMIT; i++) {
		if (!sieve[i])
			continue;

		product *= i;

		if (product >= limit)
			break;
		else
			count++;
	}

	return count;
}

static void fill_factor_arrays (int * factors, int * powers, const bool * sieve, size_t count) {
	size_t j = 0;

	for (int i = 2; j < count; i++) {
		if (!sieve[i])
			continue;

		factors[j] = i;
		powers[j] = 0;
		j++;
	}
}
