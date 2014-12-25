#include <assert.h>
#include <stdio.h>
#include "linked_list.h"
#include "utils.h"

static void linked_list_create_test ();
static void linked_list_copy_test ();
static void linked_list_add_test ();
static void linked_list_add_sorted_test ();
static void linked_list_append_test ();
static void linked_list_insert_after_test ();
static void linked_list_add_array_test ();
static void linked_list_append_array_test ();
static void linked_list_stop_iteration_test ();
static void linked_list_delete_test ();

int main () {
	linked_list_create_test ();
	linked_list_copy_test ();
	linked_list_add_test ();
	linked_list_add_sorted_test ();
	linked_list_append_test ();
	linked_list_insert_after_test ();
	linked_list_add_array_test ();
	linked_list_append_array_test ();
	linked_list_stop_iteration_test ();
	linked_list_delete_test ();

	printf ("All linked list tests passed\n");

	return 0;
}

static void linked_list_create_test () {
	linked_list_t * l = linked_list_create ();

	assert (l != NULL);

	linked_list_free (l);
}

static void linked_list_copy_test () {
	linked_list_t * l = linked_list_create ();

	int * p = NULL;

	p = linked_list_append_empty (l, int);
	*p = 10;

	p = linked_list_append_empty (l, int);
	*p = 20;

	linked_list_t * c = linked_list_copy (l, int);

	p = linked_list_next (c, int);
	assert (*p == 10);

	p = linked_list_next (c, int);
	assert (*p == 20);

	linked_list_free (l);
	linked_list_free (c);
}

static void linked_list_add_test () {
	linked_list_t * l = linked_list_create ();

	linked_list_add (l, copy_int (123));

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

static void linked_list_add_sorted_test () {
	linked_list_t * l = linked_list_create ();

	linked_list_add_sorted (l, copy_int (200), int_cmp, true);
	linked_list_add_sorted (l, copy_int (100), int_cmp, true);
	linked_list_add_sorted (l, copy_int (150), int_cmp, true);
	linked_list_add_sorted (l, copy_int (150), int_cmp, true);

	int * i_ptr = linked_list_next (l, int);
	assert (*i_ptr == 100);

	i_ptr = linked_list_next (l, int);
	assert (*i_ptr == 150);

	i_ptr = linked_list_next (l, int);
	assert (*i_ptr == 200);

	assert (linked_list_next (l, char) == NULL);

	linked_list_free (l);

	l = linked_list_create ();

	linked_list_add_sorted (l, copy_int (200), int_cmp, false);
	linked_list_add_sorted (l, copy_int (100), int_cmp, false);
	linked_list_add_sorted (l, copy_int (150), int_cmp, false);
	linked_list_add_sorted (l, copy_int (150), int_cmp, false);

	i_ptr = linked_list_next (l, int);
	assert (*i_ptr == 100);

	i_ptr = linked_list_next (l, int);
	assert (*i_ptr == 150);

	i_ptr = linked_list_next (l, int);
	assert (*i_ptr == 150);

	i_ptr = linked_list_next (l, int);
	assert (*i_ptr == 200);

	assert (linked_list_next (l, char) == NULL);

	linked_list_free (l);
}

static void linked_list_append_test () {
	linked_list_t * l = linked_list_create ();

	linked_list_append (l, copy_int (123));

	int * value2 = linked_list_append_empty (l, int);
	*value2 = 456;

	int * value = linked_list_next (l, int);
	assert (*value == 123);

	value = linked_list_next (l, int);
	assert (*value == 456);

	linked_list_free (l);
}

static void linked_list_insert_after_test () {
	linked_list_t * l = linked_list_create ();

	list_node_t * n_ptr = linked_list_append (l, copy_int (123));

	linked_list_insert_after (l, n_ptr, copy_int (456));
	linked_list_insert_after (l, n_ptr, copy_int (789));

	int * value = linked_list_next (l, int);
	assert (*value == 123);

	value = linked_list_next (l, int);
	assert (*value == 789);

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

	linked_list_add (l, copy_int (123));
	linked_list_add (l, copy_int (456));

	int * value = NULL;

	value = linked_list_next (l, int);
	assert (*value == 456);

	linked_list_stop_iteration (l);

	value = linked_list_next (l, int);
	assert (*value == 456);

	linked_list_free (l);
}

static void linked_list_delete_test () {
	linked_list_t * l = linked_list_create ();

	linked_list_append (l, copy_int (111));
	linked_list_append (l, copy_int (222));
	linked_list_append (l, copy_int (333));

	int * value = NULL;

	(void) linked_list_next (l, int);
	value = linked_list_next (l, int);

	linked_list_stop_iteration (l);

	linked_list_delete (l, value);

	value = linked_list_next (l, int);

	assert (*value == 111);

	value = linked_list_next (l, int);

	assert (*value == 333);

	value = linked_list_next (l, int);

	assert (value == NULL);

	linked_list_free (l);
}
