/*
 * Find the N-th integer that is equal to some power of the sum of its digits
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "utils.h"
#include "math_utils.h"
#include "linked_list.h"

static int get_digit_sum (long);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1)
		return 1;

	int max_digit_sum = (integer_log10 (LONG_MAX) + 1) * 9;

	linked_list_t * sequence = linked_list_create ();

	for (int digit_sum = 2; digit_sum <= max_digit_sum; digit_sum++)
		for (long power = 1; power <= LONG_MAX / digit_sum; power *= digit_sum) {
			if (power < 10)
				continue;

			if (get_digit_sum (power) == digit_sum)
				linked_list_add_sorted (sequence, copy_long (power), long_cmp, true);
		}

	long * p_ptr = NULL;

	for (int i = 0; i < N; i++)
		if ((p_ptr = linked_list_next (sequence, long)) == NULL)
			return 1;

	printf ("%ld\n", *p_ptr);

	linked_list_free (sequence);

	return 0;
}

static int get_digit_sum (long num) {
	int sum = 0;

	while (num > 0) {
		sum += num % 10;
		num /= 10;
	}

	return sum;
}
