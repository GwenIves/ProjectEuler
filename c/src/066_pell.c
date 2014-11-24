/*
 * Find n, 1 <= n <= N, for which the Pell's equation x^2 + n*y^2 = 1 has the largest minimal solution
 */

#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "bignum.h"
#include "continued_fraction.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1)
		return 1;

	int integral_sqrt = 1;

	bignum_t * max = bignum_get (0);
	int n_when_max = 0;

	for (int n = 1; n <= N; n++) {
		// There is no solution for perfect squares
		if (n == integral_sqrt * integral_sqrt) {
			integral_sqrt++;
			continue;
		}

		// x,y are integral solutions to the x^2 + n*y^2 = 1 only if x/y is a convergent of the sqrt (n) continued fraction
		linked_list_t * coefficients = linked_list_create ();

		cf_sqrt_step_t frac;

		frac.num = n;
		frac.step = 0;

		while (true) {
			cf_expand_sqrt_continued_fraction (&frac);

			linked_list_add_copy (coefficients, &frac.a, int);

			cf_convergent_t convergent = cf_evaluate (coefficients);

			bignum_t * x2 = bignum_mult (convergent.nominator, convergent.nominator);
			bignum_t * y2 = bignum_mult (convergent.denominator, convergent.denominator);

			x2 = bignum_add_to (x2, bignum_mult_to (y2, -n));

			bignum_delete (convergent.denominator);

			if (bignum_is_digit (x2, 1)) {
				if (bignum_cmp (convergent.nominator, max) > 0) {
					bignum_delete (max);
					max = convergent.nominator;
					n_when_max = n;
				} else
					bignum_delete (convergent.nominator);

				bignum_delete (x2);
				break;
			} else {
				bignum_delete (convergent.nominator);
				bignum_delete (x2);
			}
		}

		linked_list_free (coefficients);
	}

	bignum_delete (max);

	printf ("%d\n", n_when_max);

	return 0;
}
