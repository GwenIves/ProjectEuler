/*
 * Find how many continued fraction representations of sqrt (x) for 1 <= x <= N have an odd period
 */

#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "continued_fraction.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 1)
		return 1;

	int count = 0;

	for (int i = 1; i <= N; i++) {
		cf_sqrt_step_t frac;

		frac.num = i;
		frac.step = 0;

		linked_list_t * fractions = linked_list_create ();

		// All quadratic irrationals must eventually reach a cycle
		while (cf_expand_sqrt_continued_fraction (&frac)) {
			cf_sqrt_step_t * f = NULL;

			bool cycle_found = false;

			while ((f = linked_list_next (fractions, cf_sqrt_step_t)) != NULL)
				if (cf_sqrt_steps_identical (f, &frac)) {
					cycle_found = true;

					int cycle_len = frac.step - f->step;

					if (cycle_len % 2 == 1)
						count++;

					linked_list_stop_iteration (fractions);
					break;
				}

			if (!cycle_found)
				linked_list_add_copy (fractions, &frac, cf_sqrt_step_t);
			else
				break;
		}

		linked_list_free (fractions);
	}

	printf ("%d\n", count);

	return 0;
}
