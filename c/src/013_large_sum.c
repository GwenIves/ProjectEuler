/*
 * Find the sum of arbitrarily large numbers read from stdin
 */

#include <stdio.h>
#include <stdlib.h>
#include "bignum.h"
#include "utils.h"

int main () {
	char * line = NULL;

	bignum_t * sum = bignum_get (0);

	while (x_getline (&line, stdin) != -1) {
		sum = bignum_add_to (sum, bignum_get ((const char *) line));

		free (line);
	}

	bignum_print (sum);

	bignum_delete (sum);

	return 0;
}
