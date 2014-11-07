#include <assert.h>
#include <stdio.h>
#include "linked_list.h"
#include "utils.h"

static void linked_list_create_test ();
static void linked_list_add_test ();
static void linked_list_stop_iteration_test ();

int main () {
	linked_list_create_test ();
	linked_list_add_test ();
	linked_list_stop_iteration_test ();

	printf ("All linked list tests passed\n");

	return 0;
}

static void linked_list_create_test () {
	linked_list_t * l = linked_list_create ();

	assert (l != NULL);

	linked_list_free (l);
}

static void linked_list_add_test () {
	linked_list_t * l = linked_list_create ();

	int * value1 = x_malloc (sizeof (int));
	int * value2 = x_malloc (sizeof (int));
	int * value = NULL;

	*value1 = 123;
	*value2 = 456;

	linked_list_add (l, value1);
	linked_list_add (l, value2);

	value = linked_list_next (l, int);
	assert (*value == 456);

	value = linked_list_next (l, int);
	assert (*value == 123);

	linked_list_free (l);
}

static void linked_list_stop_iteration_test () {
	linked_list_t * l = linked_list_create ();

	int * value1 = x_malloc (sizeof (int));
	int * value2 = x_malloc (sizeof (int));
	int * value = NULL;

	*value1 = 123;
	*value2 = 456;

	linked_list_add (l, value1);
	linked_list_add (l, value2);

	value = linked_list_next (l, int);
	assert (*value == 456);

	linked_list_stop_iteration (l);

	value = linked_list_next (l, int);
	assert (*value == 456);

	linked_list_free (l);
}
