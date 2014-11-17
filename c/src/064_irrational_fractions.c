/*
 * Find how many continued fraction representations of sqrt (x) for 1 <= x <= N have an odd period
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "linked_list.h"

/*
 * Consider sqrt (num) as a continued fraction a_0 + 1 / (a_1 + 1 / (a_2 + ... ) ... )
 * The structure holds a_{step} and a representation of the remainder as 1 / (b / (sqrt (num) + c))
 * This can be expanded into a_{step + 1} by the expand_continued_fraction () function
 */
typedef struct {
	int num;
	int root_floor;
	int step;
	int a;
	int b;
	int c;
} continued_fraction_t;

static bool expand_continued_fraction (continued_fraction_t *);
static bool fractions_identical (continued_fraction_t *, continued_fraction_t *);

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
		continued_fraction_t frac;

		frac.num = i;
		frac.step = 0;

		linked_list_t * fractions = linked_list_create ();

		// All quadratic irrationals must eventually reach a cycle
		while (expand_continued_fraction (&frac)) {
			continued_fraction_t * f = NULL;

			bool cycle_found = false;

			while ((f = linked_list_next (fractions, continued_fraction_t)) != NULL)
				if (fractions_identical (f, &frac)) {
					cycle_found = true;

					int cycle_len = frac.step - f->step;

					if (cycle_len % 2 == 1)
						count++;

					linked_list_stop_iteration (fractions);
					break;
				}

			if (!cycle_found) {
				f = linked_list_add_empty (fractions, continued_fraction_t);

				memcpy (f, &frac, sizeof (frac));

			} else
				break;
		}

		linked_list_free (fractions);
	}

	printf ("%d\n", count);

	return 0;
}

static bool expand_continued_fraction (continued_fraction_t * f) {
	if (f->step == 0) {
		f->root_floor = sqrt (f->num);

		f->a = f->root_floor;
		f->b = 1;
		f->c = -f->root_floor;
	} else {
		int denom = (f->num - f->c * f->c) / f->b;

		// num is rational, fraction finite
		if (denom == 0)
			return false;

		int a = (f->root_floor - f->c) / denom;
		int c = -f->c - a * denom;

		f->a = a;
		f->b = denom;
		f->c = c;
	}

	f->step++;

	return true;
}

static bool fractions_identical (continued_fraction_t * f1, continued_fraction_t * f2) {
	if (f1->a != f2->a)
		return false;
	else if (f1->b != f2->b)
		return false;
	else if (f1->c != f2->c)
		return false;

	return true;
}
