/*
 * Find the sum of all minimal product-sum numbers of set size 2 to N
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "linked_list.h"
#include "utils.h"

typedef struct {
	int sum;
	int product;
	int factors;
} product_sum_t;

static bool is_product_sum (int, int, linked_list_t **);
static linked_list_t ** create_cache (size_t);
static void free_cache (linked_list_t **, size_t);
static void add_to_cache (linked_list_t **, int, int, int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 2)
		return 1;

	// For a set of size k, the worst case minimum is the product of 2 * k and the balance of k - 2 ones
	size_t limit = 2 * N;

	bool * mins = allocate_array (limit + 1, (bool) false);
	linked_list_t ** product_sums = create_cache (limit + 1);

	for (int k = 2; k <= N; k++)
		for (int candidate = k;; candidate++)
			if (is_product_sum (candidate, k, product_sums)) {
				mins[candidate] = true;
				break;
			}

	int sum = 0;

	for (int i = 2; i < limit ; i++)
		if (mins[i])
			sum += i;

	printf ("%d\n", sum);

	free (mins);
	free_cache (product_sums, limit + 1);

	return 0;
}

/*
 * Determine all factorisations of num and check if one exists with set_size factors
 * whose sum equals its product
 */
static bool is_product_sum (int num, int set_size, linked_list_t ** cache) {
	static int cache_size = 0;

	if (num > cache_size) {
		int limit = sqrt (num);

		cache[num] = linked_list_create ();

		add_to_cache (cache, num, num, 1);

		for (int i = 2; i <= limit; i++)
			if (num % i == 0)
				add_to_cache (cache, num, i, num / i);

		cache_size = num;
	}

	product_sum_t * p = NULL;

	while ((p = linked_list_next (cache[num], product_sum_t)) != NULL) {
		if (p->factors > set_size)
			continue;
		else if (p->product != num)
			continue;

		int ones_count = set_size - p->factors;

		if (p->sum + ones_count == num) {
			linked_list_stop_iteration (cache[num]);
			return true;
		}
	}

	return false;
}

static linked_list_t ** create_cache (size_t size) {
	linked_list_t ** cache = x_malloc (size * sizeof (linked_list_t *));

	for (size_t i = 0; i < size; i++)
		cache[i] = NULL;

	linked_list_t * one = linked_list_create ();

	product_sum_t * p = linked_list_add_empty (one, product_sum_t);

	p->sum = 0;
	p->product = 1;
	p->factors = 0;

	cache[1] = one;

	return cache;
}

static void free_cache (linked_list_t ** cache, size_t size) {
	for (size_t i = 0; i < size; i++)
		linked_list_free (cache[i]);

	free (cache);
}

static void add_to_cache (linked_list_t ** cache, int dividend, int divisor, int quotient) {
	product_sum_t * p = NULL;

	linked_list_t * product_sums = cache[dividend];

	while ((p = linked_list_next (cache[quotient], product_sum_t)) != NULL) {
		product_sum_t * new_ps = linked_list_add_empty (product_sums, product_sum_t);

		new_ps->sum = p->sum + divisor;
		new_ps->product = p->product * divisor;
		new_ps->factors = p->factors + 1;
	}
}
