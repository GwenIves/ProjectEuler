#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <stdlib.h>

typedef struct node {
	void * payload;
	struct node * next;
} list_node_t;

typedef struct {
	list_node_t * head;
	list_node_t * tail;
	list_node_t * cursor;
} linked_list_t;

#define linked_list_next(l,t) (t *) linked_list_next_ (l)
#define linked_list_add_empty(l,t) (t *) linked_list_add_empty_ (l, sizeof (t))
#define linked_list_add_empty_array(l,c,t) (t *) linked_list_add_empty_ (l, c * sizeof (t))
#define linked_list_append_empty(l,t) (t *) linked_list_append_empty_ (l, sizeof (t))
#define linked_list_append_empty_array(l,c,t) (t *) linked_list_append_empty_ (l, c * sizeof (t))

linked_list_t * linked_list_create ();
list_node_t * linked_list_add (linked_list_t *, void *);
void * linked_list_add_empty_ (linked_list_t *, size_t);
list_node_t * linked_list_append (linked_list_t *, void *);
void * linked_list_append_empty_ (linked_list_t *, size_t);
void linked_list_free (linked_list_t *);
void * linked_list_next_ (linked_list_t *);
void linked_list_stop_iteration (linked_list_t *);

#endif
