/*
 * Find the smallest difference of two pentagonal numbers for which both their sum and difference are also pentagonal
 */

#include <stdio.h>
#include <math.h>
#include "math_utils.h"

static int is_pentagonal (unsigned long);
static unsigned long search_solutions (int, unsigned long);

int main () {
	unsigned long dif = 0;
	int limit = 10;
	
	while ((dif = search_solutions (limit, 0)) == 0)
		limit *= 10;

	dif = search_solutions (0, dif);

	printf ("%lu\n", dif);

	return 0;
}

/*
 * 1/ When called with limit > 0 and current_minium == 0, the function will explore the solution space
 * considering all pentagonal numbers P_n and P_n+k for both n and k < limit
 *
 * 2/ When called with limit == 0 and current_minium == the result of a successful call from case 1, the function will
 * explore the solution space considering all pentagonal number pairs that could potentially produce a lower difference
 *
 * Returns the found difference or 0 if none exists given the specified limit (only applies to case 1)
 */
static unsigned long search_solutions (int limit, unsigned long current_minimum) {
	int	n_limit = 0;
	int	k_limit = 0;

	unsigned long minimum = current_minimum;

	if (limit > 0) {
		n_limit = limit;
		k_limit = limit;
	} else {
		n_limit = (current_minimum - 1) / 6;
		k_limit = 0;
	}

	for (unsigned long n = 1; n < n_limit; n++) {
		unsigned long n_squared = n * n;

		for (unsigned long k = 1; k < k_limit || k_limit == 0; k++) {
			unsigned long k_squared = k * k;

			unsigned long difference = (3 * k_squared + 6 * k * n - k) / 2;
			unsigned long sum = (6 * n_squared + 3 * k_squared + 6 * k * n - 2 * n - k) / 2;

			if (is_pentagonal (difference) && is_pentagonal (sum)) {
				if (minimum == 0)
					return difference;
				else if (difference < minimum)
					minimum = difference;
			}

			if (k_limit == 0 && difference > minimum)
				break;
		}
	}

	return minimum;
}

// If val is pentagonal there is a positive integer n solving n * (3n - 1) = val
static int is_pentagonal (unsigned long val) {
	unsigned long discrim = 1 + 24 * val;
	unsigned long larger_root = ROUND ((1 + sqrt (discrim)) / 6);
	unsigned long recomputed_val = larger_root * (3 * larger_root - 1) / 2;

	return val == recomputed_val;
}
