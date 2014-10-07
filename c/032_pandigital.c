/*
 * Find the sum of all products whose multiplicand/multiplier/product concatenation is N-digit pandigital
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "utils.h"
#include "math_utils.h"

typedef struct node {
	int val;
	struct node * next;
} node_t;

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1 || N > 9)
		return 1;

	char digits[DIGITS_COUNT];
	node_t * products = NULL;
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
				node_t * product = products;
				int duplicate = 0;

				while (product != NULL) {
					if (product->val == new_product) {
						duplicate = 1;
						break;
					}

					product = product->next;
				}

				if (!duplicate) {
					node_t * node = x_malloc (sizeof (node_t));
					node->val = new_product;
					node->next = products;

					products = node;
					sum += new_product;
				}
			}
		}
	}

	printf ("%d\n", sum);

	while (products != NULL) {
		node_t * node = products;

		products = products->next;
		free (node);
	}

	return 0;
}