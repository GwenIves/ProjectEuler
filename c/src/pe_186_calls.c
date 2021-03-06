/*
 * Consider a telephone network system connecting random callers generated by the
 * Lagged Fibonacci Generator
 * Find how many calls are necessary before the prime minister (id = 524287) is
 * a friend (transitive closure of making calls) of more than N percent of the network
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utils.h"
#include "random.h"

#define PM	524287

static void connect (int, int, int *, int *);
static int find_root (int, const int *);

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		return 1;
	}

	int N = atoi (argv[1]);

	if (N < 0 || N > 100)
		return 1;

	int * ids = x_malloc (LFG_MOD * sizeof (int));
	int * sizes = allocate_array (LFG_MOD, 1);

	for (int i = 0; i < LFG_MOD; i++)
		ids[i] = i;

	int calls = 0;

	while (true) {
		int caller = next_lfg_u ();
		int receiver = next_lfg_u ();

		if (caller == receiver)
			continue;

		calls++;
		connect (caller, receiver, ids, sizes);

		if (sizes[find_root (PM, ids)] * 100 >= N * LFG_MOD)
			break;
	}

	printf ("%d\n", calls);

	free (ids);
	free (sizes);

	return 0;
}

static void connect (int caller, int receiver, int * ids, int * sizes) {
	int i = find_root (caller, ids);
	int j = find_root (receiver, ids);

	if (i == j)
		return;

	if (sizes[i] < sizes[j]) {
		ids[i] = j;
		sizes[j] += sizes[i];
	} else {
		ids[j] = i;
		sizes[i] += sizes[j];
	}
}

static int find_root (int node, const int * ids) {
	while (ids[node] != node)
		node = ids[node];

	return node;
}
