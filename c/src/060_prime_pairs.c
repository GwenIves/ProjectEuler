/*
 * Find the smallest sum of N primes of which every pair's concatenation is also a prime
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "math_utils.h"
#include "linked_list.h"
#include "utils.h"

static int find_minimum (int, size_t, int *);
static bool is_a_prime_pair (int, int, bool *, size_t);
static int get_boundary (size_t, int, int *);
static int get_min_sum (linked_list_t *, size_t, int *);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 2)
		return 1;

	int sum = 0;
	int search_limit = 1300; // Hand-picked so that we find the minium in one iteration for N <= 5, can be any number
	int boundary = 0;

	while ((sum = find_minimum (N, search_limit, &boundary)) == 0)
		search_limit *= 10;

	if (boundary > search_limit) {
		search_limit = boundary;
		sum = find_minimum (N, search_limit, &boundary);
	}

	printf ("%d\n", sum);

	return 0;
}

/*
 * Iteratively search for possible n-tuples of primes under limit
 * To satisfy the pair-wise concatenation criteria, any (n+1)-tuple must be formed from
 * two n-tuples with the same prefix of size n-1
 *
 * Returns the found minimum or 0 if no set exists under limit
 * Upon a successful return, boundary will be set to the largest limit that could possibly contain a lower solution
 */
static int find_minimum (int set_size, size_t candidates_limit, int * boundary) {
	linked_list_t * tuples = linked_list_create ();

	// Gather primes, pre-calculate pair primeness checks and start the iteration by determining all eligible pairs

	bool * sieve = eratosthenes_sieve (candidates_limit);

	size_t primes_count = 0;
	int * primes = primes_under (sieve, candidates_limit, &primes_count);

	bool ** cache = allocate_matrix (primes_count, primes_count, (bool) false);

	for (size_t i = 0; i < primes_count; i++)
		for (size_t j = i + 1; j < primes_count; j++)
			if (is_a_prime_pair (primes[i], primes[j], sieve, candidates_limit)) {
				cache[i][j] = true;

				int * pair = linked_list_append_empty_array (tuples, 2, int);

				pair[0] = i;
				pair[1] = j;
			}

	free (sieve);

	// Now iterate from pairs up to set_size-tuples

	int min_prefix_sums[set_size];

	int * p = NULL;
	int * q = NULL;

	for (int size = 2; size < set_size; size++) {
		linked_list_t * new_tuples = linked_list_create ();

		while ((p = linked_list_next (tuples, int)) != NULL) {
			list_node_t * cursor = tuples->cursor;

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

		min_prefix_sums[size] = get_min_sum (tuples, size - 1, primes);

		linked_list_free (tuples);
		tuples = new_tuples;
	}

	free_matrix (cache, primes_count);

	int min_sum = get_min_sum (tuples, set_size, primes);

	*boundary = get_boundary (set_size, min_sum, min_prefix_sums);

	linked_list_free (tuples);
	free (primes);

	return min_sum;
}

static int get_min_sum (linked_list_t * tuples, size_t size, int * primes) {
	int min_prefix_sum = 0;

	int * p = NULL;

	while ((p = linked_list_next (tuples, int)) != NULL) {
		int prefix_sum = 0;

		for (size_t i = 0; i < size; i++)
			prefix_sum += primes[p[i]];

		if (min_prefix_sum == 0 || prefix_sum < min_prefix_sum)
			min_prefix_sum = prefix_sum;
	}

	return min_prefix_sum;
}

/*
 * A solution was found with a sum == local_minimum under some arbitrarily chosen limit
 * Under this limit, all formable n-tuples have a prefix sum >= min_prefix_sums[n]
 * If there is a global solution above limit, it must share an n-1 long prefix with some already found n-tuple
 * Consequently, we can determine the largest primes to be used in the suffix so that the total sum is less than local_minimum
 */
static int get_boundary (size_t set_size, int local_minimum, int * min_prefix_sums) {
	int max_boundary = 0;

	for (size_t i = 2; i < set_size; i++) {
		int boundary = (local_minimum - min_prefix_sums[i]) / (set_size - i + 1);

		if (boundary > max_boundary)
			max_boundary = boundary;
	}

	return max_boundary;
}

static bool is_a_prime_pair (int a, int b, bool * sieve, size_t sieve_size) {
	long c = concatenate (a, b);

	if (!is_prime_long (c, sieve, sieve_size, NULL, 0))
		return false;

	c = concatenate (b, a);

	if (!is_prime_long (c, sieve, sieve_size, NULL, 0))
		return false;

	return true;
}
