/*
 * Find the sum of all palindromes below N that can be expressed as a sum of consecutive squares
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "math_utils.h"
#include "linked_list.h"

static void add_palindrome (long, linked_list_t *);
static long sum_palindromes (linked_list_t *);

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
				add_palindrome (candidate, palindromes);
		}
	}

	printf ("%ld\n", sum_palindromes (palindromes));

	linked_list_free (palindromes);

	return 0;
}

static void add_palindrome (long palindrome, linked_list_t * palindromes) {
	long * p_ptr = NULL;

	while ((p_ptr = linked_list_next (palindromes, long)) != NULL)
		if (*p_ptr == palindrome) {
			linked_list_stop_iteration (palindromes);
			return;
		}

	linked_list_add_copy (palindromes, &palindrome, long);
}

static long sum_palindromes (linked_list_t * palindromes) {
	long sum = 0;

	long * p_ptr = NULL;

	while ((p_ptr = linked_list_next (palindromes, long)) != NULL)
		sum += *p_ptr;

	return sum;
}
