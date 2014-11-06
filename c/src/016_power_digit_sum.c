/*
 * Find the sum of digits in the N-th power of 2, with N >= 0
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

	if (N < 0)
		return 1;

	bignum_t * val2 = get_bignum_int (2);
	bignum_t * power = get_bignum_int (1);

	for (int i = 0; i < N; i++) {
		bignum_t * new_power = bignum_mult (power, val2);

		delete_bignum (power);
		power = new_power;
	}

	unsigned long sum = 0;

	for (int i = 0; i < power->used; i++)
		sum += power->digits[i];

	printf ("%lu\n", sum);

	delete_bignum (power);
	delete_bignum (val2);

	return 0;
}
