/*
 * Find the number n, 1 < n < N, such that n / Totient (n) is minimal and Totient (n) is a permutation of n
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "math_utils.h"
#include "linked_list.h"
#include "utils.h"

#define FULL_SEARCH_CUTOFF	500
#define STEP_SIZE		0.8

static bool search_for_solutions (bool *, size_t, int, double *, int *);
static void gather_factorisations (linked_list_t *, bool *, size_t, int, int, linked_list_t *);
static int get_exhaustive_limit (double);
static void free_factorisations (linked_list_t *);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 1)
		return 1;

	/*
	 * See problem 69 comments for details on the totient formula
	 * The x / Totient (x) ratio will tend to be minimal for x that are products of the smallest number of the largest primes
	 * For any prime x, Totient (x) = x - 1. Obviously this will never meet the permutation criterium
	 * We should therefore start the search among products of a pair of primes in an iteratively growing neighbourhood of sqrt (N)
	 * Once an arbitrary local minimum solution is found, we perform an exhaustive search among all the tuples of the same size
	 * that could possible give a lower minimum.
	 * If a better solution could be obtained among larger tuples, the search will continue there as well
	 */

	// In the worst case we will need a product of the smallest prime (2) and the largest prime x such that 2 * x < N
	bool * sieve = eratosthenes_sieve (N / 2);

	size_t primes_count = 2;
	double best_ratio = 2.0;
	int value_when_best = 0;

	while (search_for_solutions (sieve, primes_count, N, &best_ratio, &value_when_best))
		primes_count++;

	free (sieve);

	if (value_when_best > 0)
		printf ("%d\n", value_when_best);

	return 0;
}

/*
 * Searches for the best solution among products of prime_count-tuples. If it exists, it is passed to the caller via value_when_best
 * Returns an indicator whether the search should be continued among (prime_count + 1)-tuples
 */
static bool search_for_solutions (bool * sieve, size_t primes_count, int N, double * best_ratio, int * value_when_best) {
	int search_start = pow (N, 1.0 / primes_count) * STEP_SIZE;

	bool solution_found = false;
	bool factorisations_found = false;
	bool exhaustive_search = false;

	while (true) {
		linked_list_t * factorisations = linked_list_create ();

		gather_factorisations (factorisations, sieve, primes_count, search_start, N, NULL);

		linked_list_t * factors = NULL;
		factorisations_found = false;

		while ((factors = linked_list_next (factorisations, linked_list_t)) != NULL) {
			factorisations_found = true;

			int value = factors_to_value (factors);
			int totient = factors_to_totient (factors);

			if (is_permutation (value, totient)) {
				solution_found = true;

				double ratio = (double) value / totient;

				if (ratio < *best_ratio) {
					*best_ratio = ratio;
					*value_when_best = value;
				}
			}
		}

		free_factorisations (factorisations);

		if (!solution_found && search_start == 2) {
			if (factorisations_found)
				// No solution among n-tuples, but could be among (n + 1)-tuples
				return true;
			else
				// No solution or factorisation found, terminate
				return false;
		} else if (solution_found) {
			if (!exhaustive_search) {
				// Local minimum found, repeat search once more among all potentially better solutions
				exhaustive_search = true;
				search_start = get_exhaustive_limit (*best_ratio);
			} else {
				// This is the best solution for n-tuples, check if it can be improved in (n + 1)-tuples
				primes_count++;
				search_start = pow (N, 1.0 / primes_count);

				double best_n1_ratio = (double) search_start / (search_start - 1);

				if (best_n1_ratio > *best_ratio)
					return false;
				else
					return true;
			}
		}

		search_start *= STEP_SIZE;

		if (search_start < FULL_SEARCH_CUTOFF)
			search_start = 2;
	}
}

// Recursively build the list of all factorisations involving "primes" number of primes whose product is under "under" using primes larger or equal to "from"
static void gather_factorisations (linked_list_t * factorisations, bool * sieve, size_t primes, int from, int under, linked_list_t * factorisation) {
	int value =  1;

	if (factorisation)
		value = factors_to_value (factorisation);

	for (int i = from;; i++) {
		if (!sieve[i])
			continue;

		if (primes == 1) {
			if (i * value >= under)
				break;
		} else {
			if (i * i * value >= under)
				break;
		}

		linked_list_t * new_factorisation = NULL;

		if (factorisation)
			new_factorisation = linked_list_copy (factorisation, factor_t);
		else
			new_factorisation = linked_list_create ();

		factor_t * f_ptr = NULL;

		while ((f_ptr = linked_list_next (new_factorisation, factor_t)) != NULL)
			if (f_ptr->factor == i) {
				f_ptr->power++;

				linked_list_stop_iteration (new_factorisation);
				break;
			}

		if (!f_ptr) {
			f_ptr = x_malloc (sizeof (factor_t));

			f_ptr->factor = i;
			f_ptr->power = 1;

			linked_list_append (new_factorisation, f_ptr);
		}

		if (primes == 1)
			linked_list_append (factorisations, new_factorisation);
		else
			gather_factorisations (factorisations, sieve, primes - 1, i, under, new_factorisation);
	}
}

// Look for a large prime that will still produce a worse ratio (exhaustive search will start from there)
static int get_exhaustive_limit (double found_ratio) {
	for (int search_start = 4;; search_start *= 2) {
		double best_ratio = (double) search_start / (search_start - 1);

		if (best_ratio < found_ratio)
			return search_start / 2;
	}
}

static void free_factorisations (linked_list_t * factorisations) {
	linked_list_t * f_ptr = NULL;

	while ((f_ptr = linked_list_next (factorisations, linked_list_t)) != NULL)
		linked_list_free (f_ptr);

	linked_list_free_ (factorisations, false);
}
