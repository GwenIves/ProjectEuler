#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

ssize_t x_getline (char ** line, FILE * file) {
	size_t allocated = 0;

	ssize_t len = getline (line, &allocated, file); 

	if (len == -1)
		return -1;
	else if ((*line)[len - 1] == '\n') {
		(*line)[--len] = '\0';
	}

	return len;
}

void swap_chars (char * seq, size_t a, size_t b) {
	char t = seq[a];
	seq[a] = seq[b];
	seq[b] = t;
}

int string_cmp (const void * a, const void * b) {
	return strcmp (* (char **) a, * (char **) b);
}

int char_cmp (const void * a, const void * b) {
	char aa = * ((char *) a);
	char bb = * ((char *) b);

	return aa - bb;
}
