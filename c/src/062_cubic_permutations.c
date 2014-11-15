/*
 * Find the smallest cube of whose digit permutaions exactly N are cubes
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "utils.h"
#include "linked_list.h"

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
		linked_list_t * cubes = linked_list_create ();
		cube_permutation_t * p = NULL;

		int limit = cbrt (next_digit_at);

		while (i < limit) {
			long cube = i * i * i;

			char digits[MAX_DIGITS];

			snprintf (digits, 20, "%ld", cube);
			qsort (digits, strlen (digits), 1, char_cmp);

			bool is_permutation = false;

			while ((p = linked_list_next (cubes, cube_permutation_t)) != NULL)
				if (!strcmp (digits, p->digits)) {
					p->count++;
					is_permutation = true;

					linked_list_stop_iteration (cubes);
					break;
				}

			if (!is_permutation) {
				p = linked_list_add_empty (cubes, cube_permutation_t);

				strcpy (p->digits, digits);
				p->min_cube = cube;
				p->count = 1;
			}

			i++;
		}

		long min_cube = -1;

		while ((p = linked_list_next (cubes, cube_permutation_t)) != NULL)
			if (p->count == N) {
				if (min_cube == -1 || p->min_cube < min_cube)
					min_cube = p->min_cube;
			}

		linked_list_free (cubes);

		if (min_cube > -1) {
			printf ("%ld\n", min_cube);
			break;
		} else
			next_digit_at *= 10;
	}

	return 0;
}
