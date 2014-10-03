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

	bignum_t * fact = get_bignum_int (1);

	for (int i = 2; i <= N; i++) {
		bignum_t * num = get_bignum_int (i);

		bignum_t * new_fact = bignum_mult (fact, num);

		delete_bignum (fact);
		fact = new_fact;
	}

	int sum = 0;

	for (int i = 0; i < fact->used; i++)
		sum += fact->digits[i];

	printf ("%d\n", sum);

	delete_bignum (fact);

	return 0;
}
