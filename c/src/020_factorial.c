/*
 * Find the sum of the digits in N!
 */

#include <stdio.h>
#include <stdlib.h>
#include "bignum.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 0)
		return 1;

	bignum_t * fact = bignum_get (1);

	for (int i = 2; i <= N; i++) {
		bignum_t * new_fact = bignum_mult (fact, i);

		bignum_delete (fact);
		fact = new_fact;
	}

	printf ("%d\n", bignum_digits_sum (fact));

	bignum_delete (fact);

	return 0;
}
