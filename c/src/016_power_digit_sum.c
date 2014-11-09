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

	bignum_t * power = bignum_pow (2, N, -1);

	unsigned long sum = 0;

	for (int i = 0; i < power->used; i++)
		sum += power->digits[i];

	printf ("%lu\n", sum);

	bignum_delete (power);

	return 0;
}
