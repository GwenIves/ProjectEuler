/*
 * Assume that for a set of magnitude N holds that
 * for all its non-empty, disjoint subsets A, B, |A| > |B| => S(A) > S(B)
 * Find how many subset sums need to be tested for equality to determine
 * whether for all non-empty, disjoint subsets A, B, S(A) != S(B)
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

static bool must_check (const char *);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1)
		return 1;

	int count = 0;

	/*
	 * We only need to check subsets of equal size, see problems 103 and 105 as to why
	 *
	 * However, we can avoid many of these as well - with elements ordered in a strictly
	 * increasing order, we can look at subset selection masks and extract element
	 * pairs (x, y) such that x, y are minimal not yet taken elements, x from A and y from B
	 *
	 * If for all such x, y, x < y, then sum (A) < sum (B) and we can safely skip these subsets
	 * Should the sign reverse for a single element pair though, we cannot make any claims
	 * about the relation of sum (A) and sum (B) and those subsets will have to be tested
	 */

	for (int i = 2; i <= N / 2; i++) {
		char subsets_mask[i + i + 1];

		for (int j = 0; j < i; j++)
			subsets_mask[j] = '1';

		for (int j = i; j < i + i; j++)
			subsets_mask[j] = '2';

		subsets_mask[i + i] = '\0';

		int magnitudes[] = {i + i, N - i - i};

		/*
		 * We only care about the relative position of elements in A and B.
		 * Elements in neither set can be freely permuted in the mask without changing
		 * the result of must_check (). So avoid permuting needlessly and simply count them
		 */
		int permutations = permutations_count (magnitudes, 2);

		do {
			if (must_check (subsets_mask))
				count += permutations;
		} while (next_permutation (subsets_mask + 1));
	}

	printf ("%d\n", count);

	return 0;
}

static bool must_check (const char * mask) {
	char control = mask[0];
	int control_sum = 0;

	for (size_t i = 0; mask[i] != '\0'; i++) {
		if (mask[i] == control)
			control_sum++;
		else
			control_sum--;

		// At least one sign differs, must check sums
		if (control_sum < 0)
			return true;
	}

	return false;
}
