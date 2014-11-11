/*
 * Find how many of the first N iterations of the continued fraction representation of sqrt (2) have more digits in the numerator than denominator
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

	if (N < 1)
		return 1;

	int count = 0;

	// Iteratively compute the continued fraction 1 + p / q
	// p / q in step i becomes q / (p + 2q) in step i + 1
	// Hence, given the starting values, gcd (p, q) will always be 1 and fraction reductions are not necessary

	bignum_t * nominator = bignum_get (0);
	bignum_t * denominator = bignum_get (1);

	for (int i = 0; i < N; i++) {
		// Add 2
		nominator = bignum_add_to (nominator, bignum_mult (denominator, 2));

		// Invert
		bignum_t * t = nominator;
		nominator = denominator;
		denominator = t;

		// Add 1 for test
		bignum_t * test_nominator = bignum_add (nominator, denominator);

		if (test_nominator->used > denominator->used)
			count++;

		bignum_delete (test_nominator);
	}

	printf ("%d\n", count);

	bignum_delete (nominator);
	bignum_delete (denominator);

	return 0;
}
