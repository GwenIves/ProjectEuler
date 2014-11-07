#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

static void malloc_test ();
static void calloc_test ();
static void realloc_test ();
static void getline_test ();
static void swap_chars_test ();
static void string_cmp_test ();

#define ALLOC_SIZE	100

int main () {
	malloc_test ();
	calloc_test ();
	realloc_test ();
	getline_test ();
	swap_chars_test ();
	string_cmp_test ();

	printf ("All util tests passed\n");

	return 0;
}

static void malloc_test () {
	int * p = x_malloc (ALLOC_SIZE * sizeof (int));

	assert (p != NULL);

	free (p);
}

static void calloc_test () {
	int * p = x_calloc (ALLOC_SIZE,  sizeof (int));

	assert (p != NULL);

	for (size_t i = 0; i < ALLOC_SIZE; i++)
		assert (p[i] == 0);

	free (p);
}

static void realloc_test () {
	char * p = x_realloc (NULL, ALLOC_SIZE);

	assert (p != NULL);

	const char * test_string = "Hello, world!";

	strcpy (p, test_string);

	p = x_realloc (p, 2 * ALLOC_SIZE);

	assert (!strcmp (p, test_string));

	free (p);
}

static void getline_test () {
	char * filename = __FILE__;

	if (strrchr (filename, '/'))
		filename = strrchr (filename, '/') + 1;

	FILE * f = fopen (filename, "r");

	assert (f != NULL);

	char * line = NULL;
	ssize_t len = x_getline (&line, f);

	assert (len == 19);
	assert (!strcmp (line, "#include <assert.h>"));

	free (line);

	fclose (f);
}

static void swap_chars_test () {
	char test_str[] = "ab";

	swap (test_str, 0, 1);

	assert (!strcmp (test_str, "ba"));
}

static void string_cmp_test () {
	char * strings[] = {"b", "a"};

	qsort (strings, 2, sizeof (char *), string_cmp);

	assert (!strcmp (strings[0], "a"));
	assert (!strcmp (strings[1], "b"));
}
