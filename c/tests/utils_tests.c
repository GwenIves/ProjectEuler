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
static void array_len_test ();
static void string_cmp_test ();
static void char_cmp_test ();
static void int_cmp_test ();
static void allocate_matrix_test ();
static void allocate_array_test ();

#define ALLOC_SIZE	100

int main () {
	malloc_test ();
	calloc_test ();
	realloc_test ();
	getline_test ();
	swap_chars_test ();
	array_len_test ();
	string_cmp_test ();
	char_cmp_test ();
	int_cmp_test ();
	allocate_matrix_test ();
	allocate_array_test ();

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

static void array_len_test () {
	int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	assert (array_len (array) == 10);
}

static void string_cmp_test () {
	char * strings[] = {"b", "a"};

	qsort (strings, 2, sizeof (char *), string_cmp);

	assert (!strcmp (strings[0], "a"));
	assert (!strcmp (strings[1], "b"));
}

static void char_cmp_test () {
	char string[] = "hello char";

	qsort (string, strlen (string), 1, char_cmp);

	assert (!strcmp (string, " acehhllor"));
}

static void int_cmp_test () {
	int ints[] = {5,3,8};

	qsort (ints, array_len (ints), sizeof (int), int_cmp);

	assert (ints[0] == 3);
	assert (ints[1] == 5);
	assert (ints[2] == 8);
}

static void allocate_matrix_test () {
	int ** im = allocate_matrix (10, 10, 1);

	assert (im[0][0] == 1);
	assert (im[9][9] == 1);

	free_matrix (im, 10);

	bool ** bm = allocate_matrix (10, 10, (bool) true);

	assert (bm[0][0]);
	assert (bm[9][9]);

	free_matrix (bm, 10);
}

static void allocate_array_test () {
	int * ia = allocate_array (10, 1);

	assert (ia[0] == 1);
	assert (ia[9] == 1);

	free (ia);

	bool * ba = allocate_array (10, (bool) true);

	assert (ba[0]);
	assert (ba[9]);

	free (ba);
}
