/*
 * Consider repunits of length n, R(n), where gcd(n, 10) == 1
 * Let A(n) be the smallest n such that n divides R(n)
 * Find the smallest n for which A(n) exceeds N
 */

#include <stdio.h>
#include <stdlib.h>
#include "euler_utils.h"

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
