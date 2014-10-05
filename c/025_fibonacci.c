/*
 * Find the first term in the Fibonacci series to have N digits
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

	if (N <= 1) {
		printf ("1\n");
		return 0;
	}

	bignum_t * fib1 = get_bignum_int (0);
	bignum_t * fib2 = get_bignum_int (1);
	bignum_t * fib = NULL;

	int term = 1;

	do {
		fib = bignum_add (fib1, fib2);
		term++;

		if (fib->used == N) {
			printf ("%d\n", term);
			break;
		}

		delete_bignum (fib1);

		fib1 = fib2;
		fib2 = fib;
	} while (1);

	delete_bignum (fib1);
	delete_bignum (fib2);
	delete_bignum (fib);

	return 0;
}
