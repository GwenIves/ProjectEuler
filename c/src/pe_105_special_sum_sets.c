/*
 * Find all special sum sets on stdin and compute the sum of their sums
 * The stdin format should be one set per line as a comma-separated list
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "euler_utils.h"

int main (void) {
	size_t size = 0;
	int * set = NULL;

	long sum = 0;

	while ((set = csv_parse_int (stdin, &size)) != NULL) {
		qsort (set, size, sizeof (int), int_cmp);

		if (is_special_sum_set (set, size))
			sum += sum_array_int (set,size);

		free (set);
	}

	printf ("%ld\n", sum);

	return 0;
}
