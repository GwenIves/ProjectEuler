/*
 * Find the smallest difference of two pentagonal numbers for which both their sum and difference are also pentagonal
 */

#include <stdio.h>
#include "math_utils.h"

static int search_solutions (int, int);

int main () {
	int dif = 0;
	int limit = 10;
	
	while ((dif = search_solutions (limit, 0)) == 0)
		limit *= 10;

	dif = search_solutions (0, dif);

	printf ("%d\n", dif);

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
static int search_solutions (int limit, int current_minimum) {
	int	n_limit = 0;
	int	k_limit = 0;

	int minimum = current_minimum;

	if (limit > 0) {
		n_limit = limit;
		k_limit = limit;
	} else {
		// Largest possible n that could give a smaller difference (when k == 1)
		n_limit = (current_minimum - 1) / 3;
		k_limit = 0;
	}

	for (int n = 1; n < n_limit; n++) {
		int n_squared = n * n;

		for (int k = 1; k < k_limit || k_limit == 0; k++) {
			int k_squared = k * k;

			int difference = (3 * k_squared + 6 * k * n - k) / 2;
			int sum = (6 * n_squared + 3 * k_squared + 6 * k * n - 2 * n - k) / 2;

			if (k_limit == 0 && difference > minimum)
				break;
			else if (is_pentagonal (difference) && is_pentagonal (sum)) {
				if (minimum == 0)
					return difference;
				else if (difference < minimum)
					minimum = difference;
			}
		}
	}

	return minimum;
}
