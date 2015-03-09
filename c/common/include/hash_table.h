#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include <stdlib.h>
#include <stdbool.h>
#include "linked_list.h"

#define hash_table_fetch(h,k,t) ((t *) hash_table_fetch_ (h, k))

typedef struct {
	linked_list_t ** base;
	size_t size;
} hash_table_t;

typedef struct {
	const char * key;
	void * payload;
} hash_table_node_t;

hash_table_t * hash_table_create (size_t);
void hash_table_free (hash_table_t *);
bool hash_table_insert (hash_table_t *, const char *, void *);
void * hash_table_fetch_ (hash_table_t *, const char *);

#endif
