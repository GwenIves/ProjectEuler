#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include <stdlib.h>
#include <stdbool.h>
#include "linked_list.h"

#define hash_table_insert(H,K,D) _Generic((K), \
	int: hash_table_insert_long, \
	long: hash_table_insert_long, \
	char *: hash_table_insert_str, \
	const char *: hash_table_insert_str)(H,K,D)

#define hash_table_fetch(H,K,D) ((D *) _Generic((K), \
	int: hash_table_fetch_long, \
	long: hash_table_fetch_long, \
	char *: hash_table_fetch_str, \
	const char *: hash_table_fetch_str)(H,K))

typedef struct {
	linked_list_t ** base;
	size_t size;
} hash_table_t;

typedef struct {
	const char * key_str;
	long key_long;
	void * payload;
} hash_table_node_t;

hash_table_t * hash_table_create (size_t);
void hash_table_free (hash_table_t *);
bool hash_table_insert_str (hash_table_t *, const char *, void *);
bool hash_table_insert_long (hash_table_t *, long, void *);
void * hash_table_fetch_str (hash_table_t *, const char *);
void * hash_table_fetch_long (hash_table_t *, long);

#endif
