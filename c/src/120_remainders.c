/*
 * Find the sum of maximal remainders of dividing (a - 1)^n + (a + 1)^n by a^2 for all a, 3 <= a <= N
 */

#include <stdio.h>
#include <stdlib.h>

static int max_remainder (int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 3)
		return 1;

	int sum = 0;

	for (int a = 3; a <= N; a++)
		sum += max_remainder (a);

	printf ("%d\n", sum);

	return 0;
}

static int max_remainder (int a) {
	/*
	 * When the powers in the sum are expanded using the binomial theorem, all terms with powers >= 2 are 0 mod (a^2), so:
	 *  (a + 1) ^ n = n * a + 1 mod (a^2)
	 *  (a - 1) ^ n = n * a - 1 mod (a^2) if n is odd
	 *  (a - 1) ^ n = -n * a + 1 mod (a^2) if n is even
	 *
	 * Therefore, the remainder must be either 2 (when n is even) or 2n * a (when odd)
	 *
	 * The maximal remainder will then be the largest 2n * a < a^2
	 * that is, 2n * a for max n, n < a / 2
	 */

	int max_n = 0;

	if (a % 2 == 0)
		max_n = a / 2 - 1;
	else
		max_n = a / 2;

	return 2 * max_n * a;
}
