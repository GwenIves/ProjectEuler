/*
 * Find the smallest row that can be filled using blocks of a minimum size M
 * in more than N ways so that no two blocks are next to each other
 */

#include <stdio.h>
#include <stdlib.h>
#include "euler_utils.h"

int main (int argc, char ** argv) {
	if (argc != 3) {
		fprintf (stderr, "usage: %s <M> <N>\n", argv[0]);
		return 1;
	}

	int M = atoi (argv[1]);
	int N = atoi (argv[2]);

	if (M <= 0)
		return 1;

	int size = 1;

	while (p114_count_arrangements (size, M) <= N)
		size++;

	printf ("%d\n", size);

	return 0;
}
