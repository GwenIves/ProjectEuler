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

	if (N <= 0)
		return 1;
	else if (N == 1) {
		printf ("1\n");
		return 0;
	}

	bignum_t * fib1 = bignum_get (0);
	bignum_t * fib2 = bignum_get (1);
	bignum_t * fib = NULL;

	int term = 1;

	do {
		fib = bignum_add (fib1, fib2);
		term++;

		if (fib->used == N) {
			printf ("%d\n", term);
			break;
		}

		bignum_delete (fib1);

		fib1 = fib2;
		fib2 = fib;
	} while (true);

	bignum_delete (fib1);
	bignum_delete (fib2);
	bignum_delete (fib);

	return 0;
}
