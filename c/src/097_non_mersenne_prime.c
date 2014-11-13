/*
 * Find the last ten digits of the non-Mersenne prime 28433 * 2^7830457 + 1
 */

#include <stdio.h>
#include "bignum.h"

#define DIGITS_TO_CONSIDER	10

int main () {
	bignum_t * prime = bignum_pow (2, 7830457, DIGITS_TO_CONSIDER);

	prime = bignum_mult_to (prime, 28433);
	prime = bignum_add_to (prime, bignum_get (1));

	for (int i = DIGITS_TO_CONSIDER - 1; i >= 0; i--)
		printf ("%d", prime->digits[i]);

	printf ("\n");

	bignum_delete (prime);

	return 0;
}
