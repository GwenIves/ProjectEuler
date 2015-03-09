#include <string.h>
#include "hash_table.h"
#include "math_utils.h"
#include "utils.h"

#define HASH_MULTIPLIER	31

static size_t hash_function (const char *);
static void hash_node_free (void *);

hash_table_t * hash_table_create (size_t size) {
	while (!is_prime_long (size, NULL, 0, NULL, 0))
		size++;

	hash_table_t * hash_table = x_malloc (sizeof (hash_table_t));
	hash_table->base = x_calloc (size, sizeof (linked_list_t *));
	hash_table->size = size;

	return hash_table;
}

void hash_table_free (hash_table_t * hash_table) {
	for (size_t i = 0; i < hash_table->size; i++)
		linked_list_free (hash_table->base[i]);

	free (hash_table->base);
	free (hash_table);
}

bool hash_table_insert (hash_table_t * hash_table, const char * key, void * data) {
	if (hash_table_fetch_ (hash_table, key)) {
		free (data);
		return false;
	}

	hash_table_node_t * n_ptr = x_malloc (sizeof (hash_table_node_t));
	n_ptr->key = strdup (key);
	n_ptr->payload = data;

	linked_list_add (hash_table->base[hash_function (key) % hash_table->size], n_ptr);

	return true;
}

void * hash_table_fetch_ (hash_table_t * hash_table, const char * key) {
	size_t hash = hash_function (key) % hash_table->size;

	linked_list_t * list = hash_table->base[hash];

	if (!list) {
		list = linked_list_create ();
		linked_list_set_destructor (list, hash_node_free);

		hash_table->base[hash] = list;
	}

	hash_table_node_t * n_ptr = NULL;

	while ((n_ptr = linked_list_next (list, hash_table_node_t)) != NULL)
		if (!strcmp (n_ptr->key, key)) {
			linked_list_stop_iteration (list);
			return n_ptr->payload;
		}

	return NULL;
}

static size_t hash_function (const char * key) {
	size_t hash = 0;

	for (size_t i = 0; key[i] != '\0'; i++) {
		hash *= HASH_MULTIPLIER;
		hash += key[i];
	}

	return hash;
}

static void hash_node_free (void * n) {
	hash_table_node_t * node = (hash_table_node_t *) n;

	free ((char *) node->key);
	free (node->payload);
	free (node);
}
