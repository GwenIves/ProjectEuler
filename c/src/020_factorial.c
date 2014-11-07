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
		bignum_t * num = bignum_get (i);

		bignum_t * new_fact = bignum_mult (fact, num);

		bignum_delete (fact);
		fact = new_fact;
	}

	int sum = 0;

	for (size_t i = 0; i < fact->used; i++)
		sum += fact->digits[i];

	printf ("%d\n", sum);

	bignum_delete (fact);

	return 0;
}
