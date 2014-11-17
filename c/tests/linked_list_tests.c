#include <assert.h>
#include <stdio.h>
#include "linked_list.h"
#include "utils.h"

static void linked_list_create_test ();
static void linked_list_add_test ();
static void linked_list_append_test ();
static void linked_list_add_array_test ();
static void linked_list_append_array_test ();
static void linked_list_stop_iteration_test ();

int main () {
	linked_list_create_test ();
	linked_list_add_test ();
	linked_list_append_test ();
	linked_list_add_array_test ();
	linked_list_append_array_test ();
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
	*value1 = 123;
	linked_list_add (l, value1);

	int * value2 = linked_list_add_empty (l, int);
	*value2 = 456;

	int value3 = 789;

	linked_list_add_copy (l, &value3, int);

	int * value = linked_list_next (l, int);
	assert (*value == 789);

	value = linked_list_next (l, int);
	assert (*value == 456);

	value = linked_list_next (l, int);
	assert (*value == 123);

	linked_list_free (l);
}

static void linked_list_append_test () {
	linked_list_t * l = linked_list_create ();

	int * value1 = x_malloc (sizeof (int));
	*value1 = 123;
	linked_list_append (l, value1);

	int * value2 = linked_list_append_empty (l, int);
	*value2 = 456;

	int * value = linked_list_next (l, int);
	assert (*value == 123);

	value = linked_list_next (l, int);
	assert (*value == 456);

	linked_list_free (l);
}

static void linked_list_add_array_test () {
	linked_list_t * l = linked_list_create ();

	int * a = linked_list_add_empty_array (l, 2, int);

	a[0] = 1;
	a[1] = 9;

	a = linked_list_next (l, int);

	assert (a[0] == 1);
	assert (a[1] == 9);

	linked_list_free (l);
}

static void linked_list_append_array_test () {
	linked_list_t * l = linked_list_create ();

	int * a = linked_list_append_empty_array (l, 2, int);

	a[0] = 1;
	a[1] = 9;

	a = linked_list_next (l, int);

	assert (a[0] == 1);
	assert (a[1] == 9);

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
