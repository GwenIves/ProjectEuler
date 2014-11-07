/*
 * Find the largest prime factor of N
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	long N = ABS (atol (argv[1]));

	if (N <= 1) {
		printf ("0\n");
		return 0;
	}

	linked_list_t * factors = factorise (N);

	factor_t * f = linked_list_next (factors, factor_t);
	printf ("%lu\n", f->factor);

	linked_list_free (factors);

	return 0;
}
