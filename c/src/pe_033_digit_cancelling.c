/*
 * Consider all fractions less than 1 with both nominator and denominator N-digit numbers
 * Find all of the fractions that can be reduced by "cancelling" common digits, excluding trailing 0s
 * Then print out the denominator of their product given in its most simplified form
 */

#include <stdio.h>
#include <stdlib.h>
#include "fraction.h"
#include "math_utils.h"

static bool cancel_digit (int, int, int);
static void fill_digits (int *, int);
static int digits_to_num (const int *, int, int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 0)
		return 1;

	int start = power (10, N - 1);
	int stop = start * 10 - 1;

	fraction_t product = fraction_get (1, 1);

	for (int i = start; i < stop; i++)
		for (int j = i + 1; j <= stop; j++)
			if (cancel_digit (i, j, N)) {
				fraction_t new_frac = fraction_get (i, j);
				product = fraction_mult (&product, &new_frac);
			}

	printf ("%d\n", product.denominator);

	return 0;
}

static bool cancel_digit (int nom, int denom, int N) {
	int nom_digits[N];
	int denom_digits[N];

	fill_digits (nom_digits, nom);
	fill_digits (denom_digits, denom);

	bool nom_trailing_zero = true;

	for (int i = 0; i < N; i++) {
		if (nom_digits[i] != 0)
			nom_trailing_zero = false;

		if (nom_trailing_zero)
			continue;

		bool denom_trailing_zero = true;

		for (int j = 0; j < N; j++) {
			if (denom_digits[j] != 0)
				denom_trailing_zero = false;

			if (denom_trailing_zero)
				continue;

			if (nom_digits[i] == denom_digits[j]) {
				int new_nom = digits_to_num (nom_digits, N, i);
				int new_denom = digits_to_num (denom_digits, N, j);

				if (nom * new_denom == denom * new_nom)
					return true;
			}
		}
	}

	return false;
}

static void fill_digits (int * digits, int value) {
	int index = 0;

	do {
		digits[index++] = value % 10;
		value /= 10;
	} while (value > 0);
}

static int digits_to_num (const int * digits, int len, int ignore_index) {
	int num = 0;

	for (int i = 0; i < len; i++) {
		if (i == ignore_index)
			continue;

		num *= 10;
		num += digits[i];
	}

	return num;
}
