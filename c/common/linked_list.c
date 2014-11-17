#include <string.h>
#include "linked_list.h"
#include "utils.h"

linked_list_t * linked_list_create () {
	linked_list_t * l = x_malloc (sizeof (linked_list_t));

	l->head = NULL;
	l->tail = NULL;
	l->cursor = NULL;

	return l;
}

list_node_t * linked_list_add (linked_list_t * list, void * payload) {
	list_node_t * n = x_malloc (sizeof (list_node_t));

	n->payload = payload;
	n->next = list->head;

	list->head = n;

	if (list->tail == NULL)
		list->tail = n;

	list->cursor = n;

	return n;
}

list_node_t * linked_list_append (linked_list_t * list, void * payload) {
	list_node_t * n = x_malloc (sizeof (list_node_t));

	n->payload = payload;
	n->next = NULL;

	if (list->head == NULL) {
		list->head = n;
		list->tail = n;
		list->cursor = n;
	} else {
		list->tail->next = n;
		list->tail = n;
	}

	return n;
}

void * linked_list_append_empty_ (linked_list_t * list, size_t size) {
	list_node_t * n = linked_list_append (list, x_malloc (size));

	return n->payload;
}

void * linked_list_add_empty_ (linked_list_t * list, size_t size) {
	list_node_t * n = linked_list_add (list, x_malloc (size));

	return n->payload;
}

void * linked_list_add_copy_ (linked_list_t * list, void * payload, size_t size) {
	list_node_t * n = linked_list_add (list, x_malloc (size));

	memcpy (n->payload, payload, size);

	return n->payload;
}

void linked_list_free (linked_list_t * list) {
	while (list->head) {
		list_node_t * t = list->head->next;

		free (list->head->payload);
		free (list->head);

		list->head = t;
	}

	free (list);
}

void * linked_list_next_ (linked_list_t * list) {
	void * payload = NULL;

	if (list->cursor) {
		payload = list->cursor->payload;
		list->cursor = list->cursor->next;
	} else {
		payload = NULL;
		list->cursor = list->head;
	}

	return payload;
}

void linked_list_stop_iteration (linked_list_t * list) {
	list->cursor = list->head;
}
