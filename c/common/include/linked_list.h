#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
	void * payload;
	struct node * next;
} list_node_t;

typedef struct {
	list_node_t * head;
	list_node_t * tail;
	list_node_t * cursor;
	void (* destructor) (void *);
} linked_list_t;

#define linked_list_next(l,t) (t *) linked_list_next_ (l)
#define linked_list_add_empty(l,t) (t *) linked_list_add_empty_ (l, sizeof (t))
#define linked_list_add_copy(l,d,t) (t *) linked_list_add_copy_ (l, d, sizeof (t))
#define linked_list_add_empty_array(l,c,t) (t *) linked_list_add_empty_ (l, (c) * sizeof (t))
#define linked_list_append_empty(l,t) (t *) linked_list_append_empty_ (l, sizeof (t))
#define linked_list_append_empty_array(l,c,t) (t *) linked_list_append_empty_ (l, (c) * sizeof (t))
#define linked_list_free(l) linked_list_free_ (l, true)
#define linked_list_copy(l,t) linked_list_copy_ (l, sizeof (t))

linked_list_t * linked_list_create (void);
linked_list_t * linked_list_copy_ (linked_list_t *, size_t);
list_node_t * linked_list_add (linked_list_t *, void *);
list_node_t * linked_list_insert_after (linked_list_t *, list_node_t *, void *);
void * linked_list_add_empty_ (linked_list_t *, size_t);
void * linked_list_add_copy_ (linked_list_t *, void *, size_t);
list_node_t * linked_list_append (linked_list_t *, void *);
void * linked_list_append_empty_ (linked_list_t *, size_t);
void linked_list_add_sorted (linked_list_t *, void *, int (*) (const void *, const void *), bool);
void linked_list_set_destructor (linked_list_t *, void (*) (void *));
void linked_list_free_ (linked_list_t *, bool);
void * linked_list_next_ (linked_list_t *);
void linked_list_stop_iteration (linked_list_t *);
void linked_list_delete (linked_list_t *, void *);

long linked_list_sum_int (linked_list_t *);
long linked_list_sum_long (linked_list_t *);

#endif
