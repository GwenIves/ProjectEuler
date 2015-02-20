/*
 * Find all special sum sets on stdin and compute the sum of their sums
 * The stdin format should be one set per line as a comma-separated list
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "math_utils.h"

static bool is_special_sum_set (int *, size_t);
static int sum_set (const int *, size_t);

int main (void) {
	size_t size = 0;
	int * set = NULL;

	long sum = 0;

	while ((set = csv_parse_int (stdin, &size)) != NULL) {
		if (is_special_sum_set (set, size))
			sum += sum_set (set,size);

		free (set);
	}

	printf ("%ld\n", sum);

	return 0;
}

static bool is_special_sum_set (int * set, size_t size) {
	if (size < 2)
		return true;

	qsort (set, size, sizeof (int), int_cmp);

	/*
	 * Establish whether for all non-empty, disjoint subsets A, B, |A| > |B| => S(A) > S(B)
	 * Should this property hold for all A, B where A contains x smallest items and B
	 * x - 1 largest items from the set, then it holds for all required subsets
	 */
	int sum_smallest = set[0];
	int sum_largest = 0;

	for (size_t i = 1, j = size - 1; i < j; i++, j--) {
		sum_smallest += set[i];
		sum_largest += set[j];

		if (sum_smallest <= sum_largest)
			return false;
	}

	/*
	 * Establish whether for all non-empty, disjoint subsets A, B, S(A) != S(B)
	 * Since we have already established that non-empty, disjoint subsets of different
	 * magnitudes have different sums, we only need to check subsets of the same magnitude here
	 */
	for (size_t i = 1; i <= size / 2; i++) {
		char subsets_mask[size + 1];

		for (size_t j = 0; j < i; j++)
			subsets_mask[j] = '2';

		for (size_t j = i; j < i + i; j++)
			subsets_mask[j] = '1';

		for (size_t j = i + i; j < size; j++)
			subsets_mask[j] = '0';

		subsets_mask[size] = '\0';

		do {
			int sum1 = 0;
			int sum2 = 0;

			for (size_t j = 0; j < size; j++)
				if (subsets_mask[j] == '1')
					sum1 += set[j];
				else if (subsets_mask[j] == '2')
					sum2 += set[j];

			if (sum1 == sum2)
				return false;
		} while (prev_permutation (subsets_mask));
	}

	return true;
}

static int sum_set (const int * set, size_t size) {
	int sum = 0;

	for (size_t i = 0; i < size; i++)
		sum += set[i];

	return sum;
}
