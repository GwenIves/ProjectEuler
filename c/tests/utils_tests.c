#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "utils.h"

static void malloc_test (void);
static void calloc_test (void);
static void realloc_test (void);
static void getline_test (void);
static void swap_chars_test (void);
static void array_len_test (void);
static void string_cmp_test (void);
static void char_cmp_test (void);
static void int_cmp_test (void);
static void long_cmp_test (void);
static void allocate_matrix_test (void);
static void allocate_array_test (void);
static void copy_int_test (void);
static void copy_long_test (void);
static void csv_parse_int_test (void);
static void sum_array_int_test (void);

#define ALLOC_SIZE	100

int main (void) {
	malloc_test ();
	calloc_test ();
	realloc_test ();
	getline_test ();
	swap_chars_test ();
	array_len_test ();
	string_cmp_test ();
	char_cmp_test ();
	int_cmp_test ();
	long_cmp_test ();
	allocate_matrix_test ();
	allocate_array_test ();
	copy_int_test ();
	copy_long_test ();
	csv_parse_int_test ();
	sum_array_int_test ();

	printf ("All util tests passed\n");

	return 0;
}

static void malloc_test (void) {
	int * p = x_malloc (ALLOC_SIZE * sizeof (int));

	assert (p != NULL);

	free (p);
}

static void calloc_test (void) {
	int * p = x_calloc (ALLOC_SIZE, sizeof (int));

	assert (p != NULL);

	for (size_t i = 0; i < ALLOC_SIZE; i++)
		assert (p[i] == 0);

	free (p);
}

static void realloc_test (void) {
	char * p = x_realloc (NULL, ALLOC_SIZE);

	assert (p != NULL);

	const char * test_string = "Hello, world!";

	strcpy (p, test_string);

	p = x_realloc (p, 2 * ALLOC_SIZE);

	assert (!strcmp (p, test_string));

	free (p);
}

static void getline_test (void) {
	const char * filename = __FILE__;

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

static void swap_chars_test (void) {
	char test_str[] = "ab";

	swap (test_str, 0, 1);

	assert (!strcmp (test_str, "ba"));
}

static void array_len_test (void) {
	int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	assert (array_len (array) == 10);
}

static void string_cmp_test (void) {
	const char * strings[] = {"b", "a"};

	qsort (strings, 2, sizeof (char *), string_cmp);

	assert (!strcmp (strings[0], "a"));
	assert (!strcmp (strings[1], "b"));
}

static void char_cmp_test (void) {
	char string[] = "hello char";

	qsort (string, strlen (string), 1, char_cmp);

	assert (!strcmp (string, " acehhllor"));
}

static void int_cmp_test (void) {
	int ints[] = {5, 3, 8};

	qsort (ints, array_len (ints), sizeof (int), int_cmp);

	assert (ints[0] == 3);
	assert (ints[1] == 5);
	assert (ints[2] == 8);
}

static void long_cmp_test (void) {
	long longs[] = {5376528972765, 3237897640987, 8357123987649};

	qsort (longs, array_len (longs), sizeof (long), long_cmp);

	assert (longs[0] == 3237897640987);
	assert (longs[1] == 5376528972765);
	assert (longs[2] == 8357123987649);
}

static void allocate_matrix_test (void) {
	int ** im = allocate_matrix (10, 10, 1);

	assert (im[0][0] == 1);
	assert (im[9][9] == 1);

	free_matrix (im, 10);

	bool ** bm = allocate_matrix (10, 10, (bool) true);

	assert (bm[0][0]);
	assert (bm[9][9]);

	free_matrix (bm, 10);
}

static void allocate_array_test (void) {
	int * ia = allocate_array (10, 1);

	assert (ia[0] == 1);
	assert (ia[9] == 1);

	free (ia);

	long * la = allocate_array (10, (long) INT_MAX);

	assert (la[0] == INT_MAX);
	assert (la[9] == INT_MAX);

	free (la);

	bool * ba = allocate_array (10, (bool) true);

	assert (ba[0]);
	assert (ba[9]);

	free (ba);
}

static void copy_int_test (void) {
	int * i_ptr = copy_int (10);

	assert (*i_ptr == 10);

	free (i_ptr);
}

static void copy_long_test (void) {
	long * l_ptr = copy_long (9876543210);

	assert (*l_ptr == 9876543210);

	free (l_ptr);
}

static void csv_parse_int_test () {
	FILE * f = fopen ("../../shared/data/105_sets.in", "r");

	size_t size = 0;
	int * val = csv_parse_int (f, &size);

	assert (size == 8);
	assert (val[0] == 81);
	assert (val[7] == 65);

	free (val);
	fclose (f);

	f = fopen ("/dev/null", "r");

	size = 0;
	val = csv_parse_int (f, &size);

	assert (size == 0);
	assert (val == NULL);

	fclose (f);
}

static void sum_array_int_test (void) {
	assert (sum_array_int (NULL, 0) == 0);

	int a[] = {-10, 0, 10, 11, 12, 13, 14, 100};

	assert (sum_array_int (a, 8) == 150);
}
