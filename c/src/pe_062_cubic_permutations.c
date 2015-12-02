/*
 * Find the smallest cube of whose digit permutations exactly N are cubes
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "utils.h"
#include "hash_table.h"

#define MAX_DIGITS	20

typedef struct {
	char digits[MAX_DIGITS];
	long min_cube;
	int count;
} cube_permutation_t;

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1)
		return 1;

	long i = 1;

	long next_digit_at = 10;

	while (true) {
		hash_table_t * cubes = hash_table_create (1000);
		cube_permutation_t * p = NULL;

		int limit = cbrt (next_digit_at);
		long min_cube = -1;

		while (i < limit) {
			long cube = i * i * i;

			char digits[MAX_DIGITS];

			snprintf (digits, 20, "%ld", cube);
			qsort (digits, strlen (digits), 1, char_cmp);

			if ((p = hash_table_fetch (cubes, digits, cube_permutation_t)) != NULL)
				p->count++;
			else {
				p = x_malloc (sizeof (cube_permutation_t));

				strcpy (p->digits, digits);
				p->min_cube = cube;
				p->count = 1;

				hash_table_insert (cubes, digits, p);
			}

			if (p->count == N) {
				if (min_cube == -1 || p->min_cube < min_cube)
					min_cube = p->min_cube;
			}

			i++;
		}

		hash_table_free (cubes);

		if (min_cube > -1) {
			printf ("%ld\n", min_cube);
			break;
		} else
			next_digit_at *= 10;
	}

	return 0;
}
