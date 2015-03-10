/*
 * Find the sum of all strong repunits under N
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hash_table.h"
#include "utils.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	long N = atol (argv[1]);

	if (N < 1) {
		printf ("0\n");
		return 0;
	}

	/*
	 * We need to find all repunits for all possible bases up to N and sum those
	 * that are encountered at least twice
	 *
	 * Note that every number x is a repunit 11 in base (x - 1)
	 * Therefore, for each base we only need to consider all repunits greater than 11
	 * and can safely stop at a base sqrt (N). Every such repunit is automatically strong.
	 */

	long sum = 1;

	long base_limit = sqrt (N);

	hash_table_t * repunits = hash_table_create (base_limit);

	for (long base = 2; base <= base_limit; base++) {
		long repunit = 1 + base + base * base;

		while (repunit < N) {
			if (hash_table_insert (repunits, repunit, copy_long (repunit)))
				sum += repunit;

			repunit *= base;
			repunit++;
		}
	}

	printf ("%ld\n", sum);

	hash_table_free (repunits);

	return 0;
}
