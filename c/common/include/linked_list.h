#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

typedef struct node {
	void * payload;
	struct node * next;
} list_node_t;

typedef struct {
	list_node_t * head;
	list_node_t * cursor;
} linked_list_t;

#define linked_list_next(l,t) (t *) linked_list_next_ (l)

linked_list_t * linked_list_create ();
void linked_list_add (linked_list_t *, void *);
void linked_list_free (linked_list_t *);
void * linked_list_next_ (linked_list_t *);
void linked_list_stop_iteration (linked_list_t *);

#endif
