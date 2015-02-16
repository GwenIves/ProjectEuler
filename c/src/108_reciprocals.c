/*
 * Find the lowest n such that the equation 1/x + 1/y = 1/n
 * has more than N solutions among positive integers
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

static int divisors_count_of_a_square (int);

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
	 */

	for (int n = 1;; n++)
		if ((divisors_count_of_a_square (n) + 1) / 2 > N) {
			printf ("%d\n", n);
			break;
		}

	return 0;
}

static int divisors_count_of_a_square (int num) {
	if (num <= 1)
		return 1;

	int count = 1;

	linked_list_t * factors = factorise (num);

	factor_t * f = NULL;

	while ((f = linked_list_next (factors, factor_t)) != NULL)
		count *= 2 * f->power + 1;

	linked_list_free (factors);

	return count;
}
