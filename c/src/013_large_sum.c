/*
 * Find the sum of arbitrarily large numbers read from stdin
 */

#include <stdio.h>
#include "bignum.h"

int main () {
	char * line = NULL;
	size_t len = 0;

	bignum_t * sum = bignum_get (0);

	while (getline (&line, &len, stdin) != -1) {
		bignum_t * val = bignum_get (line);

		bignum_t * new_sum = bignum_add (sum, val);

		bignum_delete (sum);
		sum = new_sum;
	}

	bignum_print (sum);

	bignum_delete (sum);

	return 0;
}
