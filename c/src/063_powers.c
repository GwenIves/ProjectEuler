/*
 * Find how many positive integers are n-digit and an n-th integral power at the same time
 */

#include <stdio.h>
#include <stdbool.h>
#include "bignum.h"

int main () {
	int count = 0;

	for (int i = 1; i <= 9; i++) {
		int power = 0;

		bignum_t * value = bignum_get (1);

		while (true) {
			value = bignum_mult_to (value, i);
			power++;

			if (value->used == power)
				count++;
			else
				break;
		}

		bignum_delete (value);
	}

	printf ("%d\n", count);

	return 0;
}
