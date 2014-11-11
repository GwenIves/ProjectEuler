/*
 * Find the number of (tentative) Lychrel numbers under N
 */

#include <stdio.h>
#include <stdlib.h>
#include "bignum.h"

#define BREAKOFF_COUNT	50

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 1)
		return 1;

	int count = 0;

	for (int i = 1; i < N; i++) {
		bignum_t * sum = bignum_get (i);

		bool lychrel = true;

		for (int j = 0; j < BREAKOFF_COUNT; j++) {
			sum = bignum_add_to (sum, bignum_reverse (sum));

			if (bignum_is_palindrome (sum)) {
				lychrel = false;
				break;
			}
		}

		if (lychrel)
			count++;

		bignum_delete (sum);
	}

	printf ("%d\n", count);

	return 0;
}
