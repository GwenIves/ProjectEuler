/*
 * Find the special sum set of magnitude N having the smallest sum
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "euler_utils.h"
#include "math_utils.h"

static bool next_set (int *, int, const int *);
static void set_initial_set (int *, int);
static void set_boundary_set_heuristic (int *, int);
static void set_boundary_set_derived (int *, int, int);
static bool can_increase (const int *, int, const int *, int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1)
		return 1;

	int set[N];
	int boundary_set[N];

	set_initial_set (set, N);
	set_boundary_set_heuristic (boundary_set, N);

	int smallest_set[N];
	int smallest_sum = -1;

	/*
	 * In the first pass, find the smallest special sum set under the set_boundary_set_heuristic ()
	 * In the second pass, perform an exhaustive search over all sets that could possibly
	 * lower the sum
	 */
	for (int pass = 1; pass <= 2; pass++) {
		do {
			if (is_special_sum_set (set, N)) {
				int sum = sum_array_int (set, N);

				if (smallest_sum == -1 || sum < smallest_sum) {
					smallest_sum = sum;

					for (int i = 0; i < N; i++)
						smallest_set[i] = set[i];
				}
			}
		} while (next_set (set, N, boundary_set));

		if (smallest_sum == -1)
			return 1;
		else
			set_boundary_set_derived (boundary_set, N, smallest_sum);
	}

	for (int i = 0; i < N; i++)
		printf ("%d", smallest_set[i]);

	putchar ('\n');

	return 0;
}

static void set_initial_set (int * set, int size) {
	for (int i = 0; i < size; i++)
		set[i] = i + 1;
}

static void set_boundary_set_heuristic (int * set, int size) {
	set[size - 1] = 1;

	for (int i = 2; i <= size; i++) {
		int mid = set[size - i / 2];

		set[size - i] = mid;

		for (int j = size - i + 1; j < size; j++)
			set[j] += mid;
	}
}

static void set_boundary_set_derived (int * set, int size, int sum_upper_bound) {
	int smallest_element_max = sum_upper_bound - arithmetic_sequence_sum (1, size, 1);

	if (smallest_element_max % size == 0)
		smallest_element_max /= size;
	else
		smallest_element_max = smallest_element_max / size + 1;

	int worst_case_largest = 0;

	for (int i = 1; i <= smallest_element_max; i++) {
		int sum_of_two_smallest = i + i + 1;
		int sum_of_all_but_largest = arithmetic_sequence_sum (i, i + size - 1, 1);

		int largest_element_max = MIN (sum_of_two_smallest - 1, sum_upper_bound - sum_of_all_but_largest);

		if (largest_element_max > worst_case_largest)
			worst_case_largest = largest_element_max;
	}

	set[size - 1] = worst_case_largest;

	for (int i = size - 2; i >= 0; i--)
		set[i] = set[i + 1] - 1;
}

/*
 * Iterates through sets under boundary, discarding those obviously not meeting special sum set criteria
 * Set will be in strictly increasing order and all sums of n + 1 smallest elements will exceed
 * the sum of the n largest ones
 * See is_special_sum_set () for details on why
 */
static bool next_set (int * set, int size, const int * boundary) {
	int i = 0;

	for (i = size - 1; i >= 0; i--) {
		if (!can_increase (set, size, boundary, i))
			continue;

		if (i > size - i) {
			int large_sum = 0;
			int small_sum = 0;

			int inc = 1;

			for (int j = i; j < size; j++) {
				large_sum += set[i] + inc;
				inc++;
			}

			for (int j = 0; j <= size - i; j++)
				small_sum += set[j];

			if (small_sum <= large_sum)
				continue;
		}

		break;
	}

	if (i < 0)
		return false;

	set[i] += 1;

	for (int j = i + 1; j < size; j++)
		set[j] = set[j - 1] + 1;

	return true;
}

static bool can_increase (const int * set, int size, const int * boundary, int from_index) {
	for (int i = from_index; i < size; i++) {
		if (set[from_index] + i - from_index + 1 > boundary[i])
			return false;
	}

	return true;
}
