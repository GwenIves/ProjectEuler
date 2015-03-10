#include <string.h>
#include "hash_table.h"
#include "math_utils.h"
#include "utils.h"

#define HASH_MULTIPLIER	31

static size_t hash_function (const char *);
static void hash_node_free (void *);
static void ensure_list_exists (hash_table_t *, size_t);

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

bool hash_table_insert_str (hash_table_t * hash_table, const char * key, void * data) {
	if (hash_table_fetch (hash_table, key, char *)) {
		free (data);
		return false;
	}

	hash_table_node_t * n_ptr = x_malloc (sizeof (hash_table_node_t));
	n_ptr->key_str = strdup (key);
	n_ptr->payload = data;

	linked_list_add (hash_table->base[hash_function (key) % hash_table->size], n_ptr);

	return true;
}

bool hash_table_insert_long (hash_table_t * hash_table, long key, void * data) {
	if (key < 0)
		key = -key;

	if (hash_table_fetch (hash_table, key, long)) {
		free (data);
		return false;
	}

	hash_table_node_t * n_ptr = x_malloc (sizeof (hash_table_node_t));
	n_ptr->key_str = NULL;
	n_ptr->key_long = key;
	n_ptr->payload = data;

	linked_list_add (hash_table->base[key % hash_table->size], n_ptr);

	return true;
}

void * hash_table_fetch_str (hash_table_t * hash_table, const char * key) {
	size_t hash = hash_function (key) % hash_table->size;

	ensure_list_exists (hash_table, hash);

	linked_list_t * list = hash_table->base[hash];
	hash_table_node_t * n_ptr = NULL;

	while ((n_ptr = linked_list_next (list, hash_table_node_t)) != NULL)
		if (!strcmp (n_ptr->key_str, key)) {
			linked_list_stop_iteration (list);
			return n_ptr->payload;
		}

	return NULL;
}

void * hash_table_fetch_long (hash_table_t * hash_table, long key) {
	if (key < 0)
		key = -key;

	size_t hash = key % hash_table->size;

	ensure_list_exists (hash_table, hash);

	linked_list_t * list = hash_table->base[hash];
	hash_table_node_t * n_ptr = NULL;

	while ((n_ptr = linked_list_next (list, hash_table_node_t)) != NULL)
		if (n_ptr->key_long == key) {
			linked_list_stop_iteration (list);
			return n_ptr->payload;
		}

	return NULL;
}

static void ensure_list_exists (hash_table_t * hash_table, size_t hash) {
	if (!hash_table->base[hash]) {
		hash_table->base[hash] = linked_list_create ();
		linked_list_set_destructor (hash_table->base[hash], hash_node_free);
	}
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

	free ((char *) node->key_str);
	free (node->payload);
	free (node);
}
