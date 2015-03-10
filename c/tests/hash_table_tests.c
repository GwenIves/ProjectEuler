#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "hash_table.h"
#include "utils.h"

static void hash_table_create_test (void);
static void hash_table_insert_test (void);

int main (void) {
	hash_table_create_test ();
	hash_table_insert_test ();

	printf ("All hash table tests passed\n");

	return 0;
}

static void hash_table_create_test (void) {
	hash_table_t * hash_table = hash_table_create (100);

	assert (hash_table != NULL);
	assert (hash_table->base != NULL);
	assert (hash_table->size == 101);

	hash_table_free (hash_table);
}

static void hash_table_insert_test (void) {
	hash_table_t * hash_table = hash_table_create (100);

	assert (hash_table_insert (hash_table, "one", copy_int (1)));
	assert (hash_table_insert (hash_table, "two", copy_int (2)));
	assert (hash_table_insert (hash_table, "three", copy_int (3)));
	assert (hash_table_insert (hash_table, "four", copy_int (4)));
	assert (hash_table_insert (hash_table, "five", copy_int (5)));

	assert (!hash_table_insert (hash_table, "five", copy_int (5)));

	assert (*hash_table_fetch (hash_table, "one", int) == 1);
	assert (*hash_table_fetch (hash_table, "two", int) == 2);
	assert (*hash_table_fetch (hash_table, "three", int) == 3);
	assert (*hash_table_fetch (hash_table, "four", int) == 4);
	assert (*hash_table_fetch (hash_table, "five", int) == 5);

	assert (hash_table_insert (hash_table, 4, strdup ("four")));
	assert (hash_table_insert (hash_table, 5, strdup ("five")));

	assert (!hash_table_insert (hash_table, 5, strdup ("five")));

	/*
	 * FIXME: workarounds for gcc C11 type-generics code generation being too long for assert
	 *
	 * assert (!strcmp (hash_table_fetch (hash_table, 4, const char), "four"));
	 * assert (!strcmp (hash_table_fetch (hash_table, 5, const char), "five"));
	 */

	if (strcmp (hash_table_fetch (hash_table, 4, const char), "four"))
		exit (EXIT_FAILURE);

	if (strcmp (hash_table_fetch (hash_table, 5, const char), "five"))
		exit (EXIT_FAILURE);

	hash_table_free (hash_table);
}
