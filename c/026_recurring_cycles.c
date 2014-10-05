/*
 * Find the number less than N the unit fraction of which contains the longest recurring cycle
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

typedef struct {
	int remainder;
	int position;
} rem_t;

static int unit_fraction_cycle_len (int, rem_t *);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	rem_t * remainders = x_malloc (N * sizeof (rem_t));

	int longest_cycle = 0;
	int fraction = 0;

	for (int i = 1; i < N; i++) {
		int len = unit_fraction_cycle_len (i, remainders);

		if (len > longest_cycle) {
			longest_cycle = len;
			fraction = i;
		}
	}

	printf ("%d\n", fraction);

	free (remainders);

	return 0;
}

static int unit_fraction_cycle_len (int N, rem_t * remainders) {
	int num = 1;
	int position = 0;
	int past_rems = 0;

	do {
		int rem = num % N;

		for (int i = 0; i < past_rems; i++)
			if (remainders[i].remainder == rem)
				return position - remainders[i].position;

		remainders[past_rems].remainder = rem;
		remainders[past_rems].position = position;
		past_rems++;

		num = rem * 10;
		position++;
	} while (num > 0);

	return 0;
}
