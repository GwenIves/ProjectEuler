/*
 * Find the last ten digits of the sum of the series n^n for 1 <= n <= N
 */

#include <stdio.h>
#include <stdlib.h>
#include "bignum.h"
#include "math_utils.h"

#define DIGITS_TO_CONSIDER	10

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1)
		return 1;

	bignum_t * sum = bignum_get (0);

	for (int i = 1; i <= N; i++)
		sum = bignum_add_to (sum, bignum_pow (i, i, DIGITS_TO_CONSIDER));

	for (int i = MIN (DIGITS_TO_CONSIDER, sum->used) - 1; i >= 0; i--)
		printf ("%d", sum->digits[i]);

	printf ("\n");

	bignum_delete (sum);

	return 0;
}
