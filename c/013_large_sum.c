/*
 * Find the sum of arbitrarily large numbers read from stdin
 */

#include <stdio.h>
#include <stdlib.h>
#include "bignum.h"

int main (int argc, char ** argv) {
	char * line = NULL;
	size_t len = 0;

	bignum_t * sum = get_bignum_int (0);

	while (getline (&line, &len, stdin) != -1) {
		bignum_t * val = get_bignum_str (line);

		bignum_t * new_sum = bignum_add (sum, val);

		delete_bignum (sum);
		sum = new_sum;
	}

	print_bignum (sum);

	delete_bignum (sum);

	return 0;
}
