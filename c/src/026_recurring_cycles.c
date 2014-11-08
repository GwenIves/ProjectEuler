/*
 * Find the number less than N the unit fraction of which contains the longest recurring cycle
 */

#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

static int unit_fraction_cycle_len (int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1)
		return 1;

	int longest_cycle = 0;
	int fraction = 0;

	for (int i = 1; i < N; i++) {
		int len = unit_fraction_cycle_len (i);

		if (len > longest_cycle) {
			longest_cycle = len;
			fraction = i;
		}
	}

	printf ("%d\n", fraction);

	return 0;
}

// The cycle length will be the number of divisions between getting the same remainder
static int unit_fraction_cycle_len (int N) {
	int num = 1;
	int position = 0;

	int remainders[N];

	do {
		int rem = num % N;

		for (int i = 0; i < position; i++)
			if (remainders[i] == rem)
				return position - i;

		remainders[position++] = rem;

		num = rem * 10;
	} while (num > 0);

	return 0;
}
