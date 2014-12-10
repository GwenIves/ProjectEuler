/*
 * Find the smallest member of the longest amicable chain with no members above N
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "math_utils.h"
#include "linked_list.h"

#define INFINITY	-1

static int * get_divisor_sums (int);
static int get_solution (int *, int *, int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 0)
		return 1;

	int * chain_lengths = allocate_array (N + 1, 0);
	int * divisor_sums = get_divisor_sums (N + 1);

	for (int i = 1; i <= N; i++) {
		int member = i;
		int length = 0;

		linked_list_t * chain = linked_list_create ();

		while (member <= N) {
			int * m_ptr = NULL;
			bool duplicate = false;

			while ((m_ptr = linked_list_next (chain, int)) != NULL)
				if (*m_ptr == member) {
					duplicate = true;
					linked_list_stop_iteration (chain);
					break;
				}

			if (duplicate || chain_lengths[member] != 0)
				break;

			linked_list_add_copy (chain, &member, int);

			length++;
			member = divisor_sums[member];
		}

		if (member == i)
			chain_lengths[i] = length;
		else
			chain_lengths[i] = INFINITY;

		linked_list_free (chain);
	}

	printf ("%d\n", get_solution (chain_lengths, divisor_sums, N));

	free (chain_lengths);
	free (divisor_sums);

	return 0;
}

static int * get_divisor_sums (int size) {
	int * divisor_sums = allocate_array (size, 0);

	for (int i = 1; i < size; i++)
		for (int j = i + i; j < size; j += i)
			divisor_sums[j] += i;

	return divisor_sums;
}

static int get_solution (int * chain_lengths, int * divisor_sums, int size) {
	int longest_chain = 1;

	for (int i = 2; i <= size; i++)
		if (chain_lengths[i] > chain_lengths[longest_chain])
			longest_chain = i;

	int smallest_member = longest_chain;
	int member = smallest_member;

	for (int i = 1; i < chain_lengths[longest_chain]; i++) {
		member = divisor_sums[member];

		if (member < smallest_member)
			smallest_member = member;
	}

	return smallest_member;
}
