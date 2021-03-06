/*
 * Find the number of paths through an NxN lattice grid, moving only right or down
 */

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N <= 0)
		return 1;

	long grid_paths[N][N];

	for (int i = N - 1; i >= 0; i --)
		for (int j = N - 1; j >= 0; j--) {
			if (i == N - 1 && j == N - 1)
				grid_paths[i][j] = 1;
			else if (j == N - 1)
				grid_paths[i][j] = grid_paths[i + 1][j];
			else if (i == N - 1)
				grid_paths[i][j] = grid_paths[i][j + 1];
			else
				grid_paths[i][j] = grid_paths[i][j + 1] + grid_paths[i + 1][j];
		}

	printf ("%ld\n", grid_paths[0][0]);

	return 0;
}
