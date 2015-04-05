/*
 * Consider repunits of length n, R(n), where gcd(n, 10) == 1
 * Let A(n) be the smallest n such that n divides R(n)
 * Find the smallest n for which A(n) exceeds N
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

static int get_repunit_len (int);
static void extend_repunit (int *, int *, int, int);
static bool is_repunit (int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 0)
		return 1;

	/*
	 * Consider all A(i) for 0 < i <= n and assume that n divides no A(i)
	 * There are n repunits but only n - 1 residues modulo n
	 * So, for some i < j <= n, A(i) == A(j) (mod n) and n divides A(j) - A(i)
	 * Since A(j) - A(i) = R(j - i) * 10^i, n must divide the rhs
	 * Given that gcd(n, 10) == 1, n must divide R(j - i), contradicting our
	 * original assumption
	 *
	 * Therefore A(n) <= n and we can safely start the search at N + 1
	 *
	 */
	for (int i = N + 1;; i++)
		if (get_repunit_len (i) > N) {
			printf ("%d\n", i);
			break;
		}

	return 0;
}

/*
 * Keep determining a quotient longhand division style walking through the
 * repunit digits until the remainder is 0
 */
static int get_repunit_len (int divisor) {
	if (divisor % 2 == 0 || divisor % 5 == 0)
		return 0;
	else if (is_repunit (divisor))
		return 1;

	int last_divisor_digit = divisor % 10;

	int repunit = 1;
	int prev_repunit = -1;
	int len = 1;

	while (repunit % divisor != 0) {
		int quotient_digit = mult_digits[repunit % 10][last_divisor_digit];
		int product = quotient_digit * divisor;

		if (repunit < product) {
			extend_repunit (&repunit, &len, product, prev_repunit);
			prev_repunit = repunit;
		}

		repunit -= product;

		repunit /= 10;
		prev_repunit /= 10;
	}

	return len;
}

static void extend_repunit (int * cur_repunit, int * len, int product, int prev_repunit) {
	int order = 1;
	int extension = 1;

	if (prev_repunit < 0)
		while (order <= *cur_repunit)
			order *= 10;
	else
		while (prev_repunit > 0) {
			prev_repunit /= 10;
			order *= 10;
		}

	int repunit = order;

	while (repunit + *cur_repunit < product) {
		order *= 10;
		repunit += order;
		extension++;
	}

	*cur_repunit += repunit;
	*len += extension;
}

static bool is_repunit (int num) {
	switch (num) {
		case 1:
		case 11:
		case 111:
		case 1111:
		case 11111:
		case 111111:
		case 1111111:
		case 11111111:
		case 111111111:
		case 1111111111:
			return true;
		default:
			return false;
	}
}
