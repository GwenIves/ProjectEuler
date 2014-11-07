/*
 * Find the sum of arbitrarily large numbers read from stdin
 */

#include <stdio.h>
#include "bignum.h"
#include "utils.h"

int main () {
	char * line = NULL;

	bignum_t * sum = bignum_get (0);

	while (x_getline (&line, stdin) != -1) {
		bignum_t * val = bignum_get (line);

		bignum_t * new_sum = bignum_add (sum, val);

		bignum_delete (sum);
		sum = new_sum;

		free (line);
	}

	bignum_print (sum);

	bignum_delete (sum);

	return 0;
}
