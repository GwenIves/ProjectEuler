/*
 * Find the sum of all palindromes below N that can be expressed as a sum of consecutive squares
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "math_utils.h"
#include "linked_list.h"
#include "utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 0)
		return 1;

	int last_square = sqrt (N - 1);
	long limit = N;

	linked_list_t * palindromes = linked_list_create ();

	for (int first_square = 1; first_square < last_square; first_square++) {
		long candidate = first_square * first_square;

		for (int i = first_square + 1;; i++) {
			candidate += i * i;

			if (candidate >= limit)
				break;

			if (is_palindrome (candidate, 10))
				linked_list_add_sorted (palindromes, copy_long (candidate), long_cmp, true);
		}
	}

	printf ("%ld\n", linked_list_sum_long (palindromes));

	linked_list_free (palindromes);

	return 0;
}
