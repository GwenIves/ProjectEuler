/*
 * Find the last ten digits of the sum of the series n^n for 1 <= n <= N
 */

#include <stdio.h>
#include <stdlib.h>
#include "bignum.h"
#include "math_utils.h"

#define DIGITS_TO_CONSIDER	10

static bignum_t * self_power (int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1)
		return 1;

	bignum_t * sum = bignum_get (0);

	for (int i = 1; i <= N; i++) {
		bignum_t * power = self_power (i);

		bignum_t * new_sum = bignum_add (sum, power);

		bignum_delete (power);
		bignum_delete (sum);

		sum = new_sum;
	}

	for (int i = MIN (DIGITS_TO_CONSIDER, sum->used) - 1; i >= 0; i--)
		printf ("%d", sum->digits[i]);

	printf ("\n");

	bignum_delete (sum);

	return 0;
}

static bignum_t * self_power (int num) {
	bignum_t * val = bignum_get (num);
	bignum_t * result = bignum_get (1);

	for (int i = 0; i < num; i++) {
		bignum_t * new_result = bignum_mult (val, result);

		new_result->used = MIN (DIGITS_TO_CONSIDER, new_result->used);

		bignum_delete (result);
		result = new_result;
	}

	bignum_delete (val);

	return result;
}
