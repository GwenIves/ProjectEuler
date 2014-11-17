/*
 * Find the sum of numerator digits in the N-th convergent of the continued fraction of e
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

	bignum_t * nominator = bignum_get (0);
	bignum_t * denominator = bignum_get (1);

	// e = [2; 1, 2, 1, 1, 4, 1, ..., 1, 2k, 1, ... ]

	for (int i = N; i > 1; i--) {
		int a = 0;

		if (i % 3 == 0)
			a = 2 * (i / 3);
		else
			a = 1;

		nominator = bignum_add_to (nominator, bignum_mult (denominator, a));

		bignum_t * t = nominator;
		nominator = denominator;
		denominator = t;
	}

	nominator = bignum_add_to (nominator, bignum_mult (denominator, 2));

	printf ("%d\n", bignum_digits_sum (nominator));

	bignum_delete (nominator);
	bignum_delete (denominator);

	return 0;
}
