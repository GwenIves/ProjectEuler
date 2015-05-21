/*
 * Consider four integral, right-angled triangles placed together to form a square
 * There will be a hole left in the middle
 * Find how many triangles with a perimeter under N leave a hole that can tile the square
 */

#include <stdio.h>
#include <stdlib.h>
#include "math_utils.h"

static long count_triangles (int, int, int, int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 0)
		return 1;

	printf ("%ld\n", count_triangles (N, 3, 4, 5));

	return 0;
}

/*
 * Walks the ternary tree of primitive Pythagorean triples
 * The initial call should set (a, b, c) to the smallest triple (3, 4, 5)
 */
static long count_triangles (int limit, int a, int b, int c) {
	if (a + b + c >= limit)
		return 0;

	long count = 0;

	if (c % ABS (a - b) == 0) {
		// Also add all non-primitive multiples under limit
		count += (limit - 1) / (a + b + c);
	}

	int new_a = a - 2 * b + 2 * c;
	int new_b = 2 * a - b + 2 * c;
	int new_c = 2 * a - 2 * b + 3 * c;

	count += count_triangles (limit, new_a, new_b, new_c);

	new_a = a + 2 * b + 2 * c;
	new_b = 2 * a + b + 2 * c;
	new_c = 2 * a + 2 * b + 3 * c;

	count += count_triangles (limit, new_a, new_b, new_c);

	new_a = -a + 2 * b + 2 * c;
	new_b = -2 * a + b + 2 * c;
	new_c = -2 * a + 2 * b + 3 * c;

	count += count_triangles (limit, new_a, new_b, new_c);

	return count;
}
