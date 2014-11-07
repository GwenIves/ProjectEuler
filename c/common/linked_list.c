#include "linked_list.h"
#include "utils.h"

linked_list_t * linked_list_create () {
	linked_list_t * l = x_malloc (sizeof (linked_list_t));

	l->head = NULL;
	l->cursor = NULL;

	return l;
}

void linked_list_add (linked_list_t * list, void * payload) {
	list_node_t * n = x_malloc (sizeof (list_node_t));

	n->payload = payload;
	n->next = list->head;

	list->head = n;
	list->cursor = n;
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
