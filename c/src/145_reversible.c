/*
 * Find how many reversible numbers there are under N
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "math_utils.h"

static bool is_reversible (long num);
static void get_limits (int, int *, int *);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	int count = 0;
	int start_at = 1;

	/*
	 * Determines how many solutions there are
	 * under the largest power of 10 lower or equal to N
	 * by combinatorial analysis
	 * A brute-force search then proceeds from there until N
	 */
	get_limits (N, &count, &start_at);

	for (int i = start_at; i < N; i++) {
		if (i % 10 == 0)
			continue;
		else if (is_reversible (i + reverse (i, 10)))
			count++;
	}

	printf ("%d\n", count);

	return 0;
}

static bool is_reversible (long num) {
	while (num > 0) {
		if (num % 2 == 0)
			return false;

		num /= 10;
	}

	return true;
}

static void get_limits (int N, int * count_out, int * start_at_out) {
	int count = 0;
	int start_at = 0;

	if (N >= 100) {
		/*
		 * No one digit solution
		 * For two digit solutions ab, a, b > 0, a + b must be odd (for the sum's last digit to be odd)
		 * and without carry (for the sum's first digit to be odd as well)
		 * 20 possibilities
		 */
		count += 20;
		start_at = 100;
	}

	if (N >= 1000) {
		/*
		 * For three digit solutions axb, a, b > 0, a + b must be odd and with carry
		 * (otherwise the second digit of the sum, x + x, would be even)
		 * 20 possibilities
		 * x + x, x >= 0, must be without carry (otherwise the sum's first digit would be even)
		 * 5 possibilities
		 */
		count += 5 * 20;
		start_at = 1000;
	}

	if (N >= 10000) {
		/*
		 * For four digit solutions acdb, a, b > 0, c, d >= 0
		 * a + b must be odd (last digit of sum), therefore c + d without carry
		 * (otherwise the first digit of the sum would be even),
		 * therefore c + d must be odd (from definition) and a + b without a carry
		 * 20 possibilities for a, b
		 * 30 possibilities for c, d
		 */
		count += 20 * 30;
		start_at = 10000;
	}

	if (N >= 100000) {
		/*
		 * No five digit solutions acxdb
		 * c + d would have to have a carry (or the third sum digit, x + x, would be even)
		 * a + b must be odd (last sum digit) but then the first sum digit (a + b + 1) would be even
		 */
		start_at = 100000;
	}

	if (N >= 1000000) {
		// Six digit solutions acefdb - similar to four digits
		count += 20 * 30 * 30;
		start_at = 1000000;
	}

	if (N >= 10000000) {
		/*
		 * For seven digit solutions acexfdb
		 * f + e, f, e >= 0, must have a carry (otherwise the fourth sum digit, x + x, would be odd)
		 * Therefore a + b, a, b > 0, must have a carry too (or the sum's digits 2 and 6 would differ in parities)
		 * Therefore c + d must not have a carry and be even (both sum's digits receive a carry)
		 * a + d and e + f must be odd
		 * 5 possibilities for x
		 * 20 possibilities for a, b and e, f
		 * 25 possibilities for c, d
		 */
		count += 5 * 20 * 20 * 25;
		start_at = 10000000;
	}

	if (N >= 100000000) {
		// Eight digit solutions - similar to six and four digits
		count += 20 * 30 * 30 * 30;
		start_at = 100000000;
	}

	if (N >= 1000000000) {
		// No nine digit solutions - similar to five digits
		start_at = 1000000000;
	}

	*count_out = count;
	*start_at_out = start_at;
}
