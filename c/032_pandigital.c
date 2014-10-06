/*
 * Find the sum of all products whose multiplicand/multiplier/product concatenation is N-digit pandigital
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "utils.h"

#define DIGITS_LEN	10

typedef struct node {
	int val;
	struct node * next;
} node_t;

static int test_and_set_digits (char *, int);
static int test_digits (char *, int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1 || N > 9)
		return 1;

	char digits[DIGITS_LEN];
	node_t * products = NULL;
	int sum = 0;

	int max_mult = pow (10, N / 2) - 1;

	for (int i = 1; i <= max_mult; i++) {
		memset (digits, 0, DIGITS_LEN);

		if (!test_and_set_digits (digits, i))
			continue;

		for (int j = i + 1; j <= max_mult; j++) {
			char new_digits[DIGITS_LEN];

			memcpy (new_digits, digits, DIGITS_LEN);

			int new_product = i * j;

			if (!test_and_set_digits (new_digits, j))
				continue;
			else if (!test_and_set_digits(new_digits, new_product))
				continue;
			else if (test_digits (new_digits, N)) {
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

static int test_and_set_digits (char * digits, int value) {
	while (value > 0) {
		int digit = value % 10;
		value /= 10;

		if (digit == 0)
			return 0;
		else if (digits[digit])
			return 0;
		else
			digits[digit] = 1;
	}

	return 1;
}

static int test_digits (char * digits, int N) {
	for (int i = 1; i <= N; i++)
		if (digits[i] == 0)
			return 0;

	for (int i = N + 1; i < DIGITS_LEN; i++)
		if (digits[i] == 1)
			return 0;

	return 1;
}
