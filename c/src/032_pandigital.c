/*
 * Find the sum of all products whose multiplicand/multiplier/product concatenation is N-digit pandigital
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "math_utils.h"
#include "hash_table.h"
#include "utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1 || N >= DIGITS_COUNT)
		return 1;

	char digits[DIGITS_COUNT];
	hash_table_t * products = hash_table_create (1000);
	int sum = 0;

	int max_mult = power (10, N / 2) - 1;

	for (int i = 1; i <= max_mult; i++) {
		memset (digits, 0, DIGITS_COUNT);

		if (!pandigital_test_and_set_digits (digits, i))
			continue;

		for (int j = i + 1; j <= max_mult / i; j++) {
			char new_digits[DIGITS_COUNT];

			memcpy (new_digits, digits, DIGITS_COUNT);

			int new_product = i * j;

			if (!pandigital_test_and_set_digits (new_digits, j))
				continue;
			else if (!pandigital_test_and_set_digits(new_digits, new_product))
				continue;
			else if (pandigital_test_digits (new_digits, N)) {
				if (hash_table_insert (products, new_product, copy_int (new_product)))
					sum += new_product;
			}
		}
	}

	printf ("%d\n", sum);

	hash_table_free (products);

	return 0;
}
