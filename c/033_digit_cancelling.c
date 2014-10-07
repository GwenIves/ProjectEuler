/*
 * Consider all fractions less than 1 with both nominator and denominator N-digit numbers
 * Find all of the fractions that can be reduced by "cancelling" common digits, excluding trailing 0s
 * Then print out the denominator of their product given in its most simplified form
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include "fraction.h"

static int cancel_digit (int, int, int);
static int * fill_digits (int, int);
static int digits_to_num (int *, int, int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 0)
		return 1;

	int start = pow (10, N - 1);
	int stop = start * 10 - 1;

	fraction_t product = fraction_get (1, 1);

	for (int i = start; i < stop; i++)
		for (int j = i + 1; j <= stop; j++)
			if (cancel_digit (i, j, N)) {
				fraction_t new_frac = fraction_get (i, j);
				product = fraction_mult (&product, &new_frac);
			}

	printf ("%lu\n", product.denominator);

	return 0;
}

static int cancel_digit (int nom, int denom, int N) {
	int * nom_digits = fill_digits (nom, N);
	int * denom_digits = fill_digits (denom, N);

	int nom_trailing_zero = 1;

	for (int i = 0; i < N; i++) {
		if (nom_digits[i] != 0)
			nom_trailing_zero = 0;

		int denom_trailing_zero = 1;

		for (int j = 0; j < N; j++) {
			if (denom_digits[j] != 0)
				denom_trailing_zero = 0;

			if (nom_trailing_zero && denom_trailing_zero)
				continue;
			else if (nom_digits[i] == denom_digits[j]) {
				int new_nom = digits_to_num (nom_digits, N, i);
				int new_denom = digits_to_num (denom_digits, N, j);

				if (nom * new_denom == denom * new_nom) {
					free (nom_digits);
					free (denom_digits);
					
					return 1;
				}
			}
		}
	}

	free (nom_digits);
	free (denom_digits);

	return 0;
}

static int * fill_digits (int value, int len) {
	int * digits = x_malloc (len * sizeof (int));

	int index = 0;

	do {
		digits[index++] = value % 10;
		value /= 10;
	} while (value > 0);

	return digits;
}

static int digits_to_num (int * digits, int len, int ignore_index) {
	int num = 0;

	for (int i = 0; i < len; i++) {
		if (i == ignore_index)
			continue;

		num *= 10;
		num += digits[i];
	}

	return num;
}
