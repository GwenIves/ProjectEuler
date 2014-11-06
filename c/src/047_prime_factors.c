/*
 * Find the first of N consecutive numbers with N prime factors each
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int factor_count (int);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 0)
		return 1;

	int start = 0;
	int len = 0;
	int i = 2;

	while (1) {
		if (factor_count (i) >= N) {
			if (len++ == 0)
				start = i;

			if (len == N) 
				break;
		} else
			len = 0;

		i++;
	}

	printf ("%d\n", start);

	return 0;
}

static int factor_count (int num) {
	int upper_limit = sqrt (num);
	int factor = 2;
	int count = 0;

	while (num != 1) {
		if (num % factor == 0) {
			while (num % factor == 0)
				num /= factor;

			upper_limit = sqrt (num);

			count++;
		}

		if (num == 1) 
			break;
		else if (++factor > upper_limit) {
			count++;
			break;
		}
	}

	return count;
}
