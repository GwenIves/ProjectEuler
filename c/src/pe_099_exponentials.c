/*
 * Find the largest base^exponent value of all base,exponent pairs read from stdin
 * The stdin format should be one comma-separated pair per line
 * The program prints out the line number containing the largest value
 */

#include <stdio.h>
#include <math.h>

int main (void) {
	int base = 0;
	int exponent = 0;
	int lineno = 0;

	double max_log_value = 0.0;
	int max_lineno = 0;

	while (scanf ("%d,%d\n", &base, &exponent) == 2) {
		lineno++;

		double log_value = exponent * log (base);

		if (log_value > max_log_value) {
			max_log_value = log_value;
			max_lineno = lineno;
		}
	}

	if (max_lineno > 0)
		printf ("%d\n", max_lineno);

	return 0;
}
