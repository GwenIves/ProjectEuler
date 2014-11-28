/*
 * Consider all cuboids with integral sides a x b x c, a, b, c <= M,
 * such that the shortest path between opposite corners traced on the surface is also integral
 * Find the lowest M, such that the number of possible cuboids exceeds N
 */

#include <stdio.h>
#include <stdlib.h>
#include <utils.h>
#include "math_utils.h"

static int count_cuboids (int, int, int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);
	int M = 1;

	while (true) {
		int count = 0;

		bool solutions_possible = true;

		for (int n = 1; solutions_possible; n++) {
			solutions_possible = false;

			for (int m = n + 1;; m++) {
				int sides[3];

				if (!euclid_pythagorean_triple (m, n, sides, sides + 1, sides + 2))
					continue;

				qsort (sides, 3, sizeof (int), int_cmp);

				count += count_cuboids (sides[0], sides[1], M);
				count += count_cuboids (sides[1], sides[0], M);

				if (sides[0] <= M || sides[1] <= M)
					solutions_possible = true;
				else
					break;
			}
		}

		if (count > N)
			break;

		M++;
	}

	printf ("%d\n", M);

	return 0;
}

/*
 * In a matching cuboid a x b x c, a <= b <= c, the shortest path will be the hypotenuse
 * of a right angled triangle with legs a + b and c
 * This function receives a + b and c from a primitive Pythagorean triple and counts
 * all the possibilities of spliting the sum into a and b so that neither exceeds limit
 * considering all triples, including non-primitive ones
 */
static int count_cuboids (int longest_side, int sum_of_the_others, int limit) {
	int count = 0;

	for (int i = 1; longest_side * i <= limit; i++) {
		int c = longest_side * i;
		int sum = sum_of_the_others * i;

		int lowest_b = (sum + 1) / 2;
		int highest_b = MIN (sum - 1, c);

		if (highest_b >= lowest_b)
			count += highest_b - lowest_b + 1;
	}

	return count;
}
