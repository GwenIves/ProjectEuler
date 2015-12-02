/*
 * Find the product of all Pythagorean triplets with a sum equal to N
 */

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	for (int a = 1; a <= N / 3; a++) {
		int a_square = a * a;

		for (int b = a + 1; b <= N; b++) {
			int c = N - a - b;

			if (c <= b)
				break;

			if (a_square + b * b != c * c)
				continue;

			printf ("%d\n", a * b * c);
		}
	}

	return 0;
}
