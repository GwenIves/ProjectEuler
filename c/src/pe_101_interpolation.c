/*
 * Read a polynomial of order N from the argument list and evaluate it for all integers 1 to N
 * Interpolate the first n of those values for all n <= N.
 * Find the sum of all values the interpolated polynomials give for n + 1 should this value
 * fail to correctly fit the original polynomial
 *
 * The command line arguments should give all polynomial coefficients in sequence
 * starting with the constant term, .eg x^4 + 2x + 8 would be 8 2 0 0 1
 */

#include <stdio.h>
#include <stdlib.h>

static void load_coefficients (int *, char **);
static void calculate_values (long *, const int *, int, int);
static long poly_evaluate (const int *, int, int);
static long lagrange_poly_val (const long *, int, int);

int main (int argc, char ** argv) {
	if (argc < 2) {
		fprintf (stderr, "usage: %s a_0 a_1 a_2...\n", argv[0]);
		return 1;
	}

	int poly_terms = argc - 1;

	int poly_coeffs[poly_terms];
	long poly_vals[poly_terms];

	load_coefficients (poly_coeffs, argv + 1);
	calculate_values (poly_vals, poly_coeffs, poly_terms, poly_terms);

	long bop_sum = 0;

	for (int i = 1; i < poly_terms; i++) {
		long extrapolated_val = lagrange_poly_val (poly_vals, i, i + 1);

		if (extrapolated_val != poly_vals[i])
			bop_sum += extrapolated_val;
	}

	printf ("%ld\n", bop_sum);

	return 0;
}

static void load_coefficients (int * coeffs, char ** argv) {
	for (size_t i = 0; argv[i] != NULL; i++)
		coeffs[i] = atoi (argv[i]);
}

static void calculate_values (long * values, const int * coeffs, int terms, int count) {
	for (int i = 0; i < count; i++)
		values[i] = poly_evaluate (coeffs, terms, i + 1);
}

static long poly_evaluate (const int * coeffs, int terms, int x) {
	long val = 0;

	for (int i = terms - 1; i >= 0; i--) {
		val *= x;
		val += coeffs[i];
	}

	return val;
}

/*
 * This function relies on the fact that the "vals" array (y) gives values for the first "term" positive integers (x)
 * ie. x_i = i + 1 and y_i = polynom (x_i) = polynom (i + 1)
 */
static long lagrange_poly_val (const long * vals, int terms, int x) {
	long val = 0;

	for (int i = 0; i < terms; i++) {
		long nom = 1;
		long denom = 1;

		for (int j = 1; j <= terms; j++) {
			if (j != i + 1) {
				nom *= x - j;
				denom *= i + 1 - j;
			}
		}

		val += vals[i] * nom / denom;
	}

	return val;
}
