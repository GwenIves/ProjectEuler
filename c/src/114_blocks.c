/*
 * Find how many ways a row of size N can be filled using blocks of a minimum size 3
 * so that no two blocks are next to each other
 */

#include <stdio.h>
#include <stdlib.h>
#include "euler_utils.h"

#define MIN_SIZE	3

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 0)
		return 1;

	printf ("%ld\n", p114_count_arrangements (N, MIN_SIZE));

	return 0;
}
