/*
 * Find the smallest sum of N primes of which every pair's concatenation is also a prime
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"
#include "linked_list.h"
#include "utils.h"

/*
 * FIXME: Severe performance issues (~ 20 seconds for N == 5)
 * 	Optimisticaly skipping the exhaustive search part improves performance (for N == 5) by a factor of almost 20
 * 	However, the algorithm would then no longer guarantee the location of the global minimum
 */

static int find_minimum (int, size_t);
static bool is_a_prime_pair (int, int, bool *, size_t);
static bool ** create_cache (size_t);
static void free_cache (bool **, size_t);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 2)
		return 1;

	int sum = 0;
	size_t search_limit = 1000;
	
	while ((sum = find_minimum (N, search_limit)) == 0)
		search_limit *= 10;

	if (sum > search_limit)
		sum = find_minimum (N, sum);

	printf ("%d\n", sum);

	return 0;
}

/*
 * Iteratively search for possible n-tuples of primes under limit
 * To satisfy the pair-wise concatenation criteria, any (n+1)-tuple must be formed from 
 * two n-tuples with the same prefix of size n-1
 */
static int find_minimum (int set_size, size_t limit) {
	linked_list_t * tuples = linked_list_create ();

	// Gather primes, pre-calculate pair primeness checks and start the iteration by determining all eligible pairs

	bool * sieve = eratosthenes_sieve (limit + 1);

	int primes[limit];
	size_t primes_count = 0;

	for (int i = 3; i <= limit; i += 2)
		if (sieve[i])
			primes[primes_count++] = i;

	bool ** cache = create_cache (primes_count);

	for (size_t i = 0; i < primes_count; i++)
		for (size_t j = i + 1; j < primes_count; j++)
			if (is_a_prime_pair (primes[i], primes[j], sieve, limit)) {
				cache[i][j] = true;

				int * pair = linked_list_append_empty_array (tuples, 2, int);

				pair[0] = i;
				pair[1] = j;
			}

	free (sieve);

	// Now iterate from pairs up to set_size-tuples

	int * p = NULL;
	int * q = NULL;

	for (int size = 2; size < set_size; size++) {
		linked_list_t * new_tuples = linked_list_create ();

		list_node_t * cursor = NULL;

		while ((p = linked_list_next (tuples, int)) != NULL) {
			cursor = tuples->cursor;

			while ((q = linked_list_next (tuples, int)) != NULL) {
				bool same_prefix = true;

				for (int i = 0; i < size - 1; i++)
					if (q[i] != p[i]) {
						same_prefix = false;
						break;
					}

				if (same_prefix) {
					if (cache[p[size - 1]][q[size - 1]]) {
						int * n = linked_list_append_empty_array (new_tuples, size + 1, int);

						for (int i = 0; i < size; i++)
							n[i] = p[i];

						n[size] = q[size - 1];
					}
				} else {
					break;
				}
			}

			tuples->cursor = cursor;
		}

		linked_list_free (tuples);
		tuples = new_tuples;
	}

	// Return the smallest tuple's sum

	int min_sum = 0;

	while ((p = linked_list_next (tuples, int)) != NULL) {
		int sum = 0;

		for (int i = 0; i < set_size; i++)
			sum += primes[p[i]];

		if (min_sum == 0 || sum < min_sum)
			min_sum = sum;
	}

	linked_list_free (tuples);

	free_cache (cache, primes_count);

	return min_sum;
}

static bool is_a_prime_pair (int a, int b, bool * sieve, size_t limit) {
	long c = concatenate (a, b);

	if (!is_prime (sieve, c, limit))
		return false;

	c = concatenate (b, a);

	if (!is_prime (sieve, c, limit))
		return false;

	return true;
}

static bool ** create_cache (size_t primes_count) {
	bool ** cache = x_malloc (primes_count * sizeof (bool *));

	for (size_t i = 0; i < primes_count; i++) {
		cache[i] = x_malloc (primes_count * sizeof (bool));

		for (size_t j = 0; j < primes_count; j++)
			cache[i][j] = false;
	}

	return cache;
}

static void free_cache (bool ** cache, size_t cache_size) {
	free_array (cache, cache_size);
	free (cache);
}
