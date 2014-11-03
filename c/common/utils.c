#include <stdio.h>
#include <stdlib.h>

void * x_malloc (size_t size) {
	void * mem = malloc (size);

	if (!mem) {
		fprintf (stderr, "Unable to allocate memory\n");
		exit (EXIT_FAILURE);
	}

	return mem;
}

void * x_calloc (size_t count, size_t size) {
	void * mem = calloc (count, size);

	if (!mem) {
		fprintf (stderr, "Unable to allocate memory\n");
		exit (EXIT_FAILURE);
	}

	return mem;
}

void * x_realloc (void * ptr, size_t size) {
	void * mem = realloc (ptr, size);

	if (size > 0 && !mem) {
		fprintf (stderr, "Unable to allocate memory\n");
		exit (EXIT_FAILURE);
	}

	return mem;
}


void swap_chars (char * seq, int a, int b) {
	char t = seq[a];
	seq[a] = seq[b];
	seq[b] = t;
}
