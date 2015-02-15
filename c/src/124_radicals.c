/*
 * Find the number whose radical appears as N-th in an ordered list of radicals of the first M numbers
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

typedef struct {
	int number;
	int radical;
} radical_t;

static int radicals_cmp (const void *, const void *);

int main (int argc, char ** argv) {
	if (argc != 3) {
		fprintf (stderr, "usage: %s <N> <M>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);
	int M = atoi (argv[2]);

	if (M <= 0)
		return 1;
	else if (N <= 0 || N > M)
		return 1;

	radical_t * radicals = x_malloc ((M + 1) * sizeof (radical_t));

	for (int i = 0; i <= M; i++) {
		radicals[i].number = i;
		radicals[i].radical = 1;
	}

	for (int i = 2; i <= M; i++) {
		if (radicals[i].radical != 1)
			continue;

		for (int j = i; j <= M; j += i)
			radicals[j].radical *= i;
	}

	qsort (radicals, M + 1, sizeof (radical_t), radicals_cmp);

	printf ("%d\n", radicals[N].number);

	free (radicals);

	return 0;
}

static int radicals_cmp (const void * a, const void * b) {
	const radical_t * aa = a;
	const radical_t * bb = b;

	if (aa->radical != bb->radical)
		return aa->radical - bb->radical;
	else
		return aa->number - bb->number;
}
