/*
 * Find the sum of all products whose multiplicand/multiplier/product concatenation is N-digit pandigital
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "math_utils.h"
#include "linked_list.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1 || N > 9)
		return 1;

	char digits[DIGITS_COUNT];
	linked_list_t * products = linked_list_create ();
	int sum = 0;

	int max_mult = pow (10, N / 2) - 1;

	for (int i = 1; i <= max_mult; i++) {
		memset (digits, 0, DIGITS_COUNT);

		if (!pandigital_test_and_set_digits (digits, i))
			continue;

		for (int j = i + 1; j <= max_mult; j++) {
			char new_digits[DIGITS_COUNT];

			memcpy (new_digits, digits, DIGITS_COUNT);

			int new_product = i * j;

			if (!pandigital_test_and_set_digits (new_digits, j))
				continue;
			else if (!pandigital_test_and_set_digits(new_digits, new_product))
				continue;
			else if (pandigital_test_digits (new_digits, N)) {
				int duplicate = 0;

				int * product = NULL;

				while ((product = linked_list_next (products, int)) != NULL) {
					if (*product == new_product) {
						duplicate = 1;
						linked_list_stop_iteration (products);
						break;
					}
				}

				if (!duplicate) {
					int * val = linked_list_add_empty (products, int);
					*val = new_product;

					sum += new_product;
				}
			}
		}
	}

	printf ("%d\n", sum);

	linked_list_free (products);

	return 0;
}
