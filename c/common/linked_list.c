#include <string.h>
#include "linked_list.h"
#include "utils.h"

linked_list_t * linked_list_create (void) {
	linked_list_t * l = x_malloc (sizeof (linked_list_t));

	l->head = NULL;
	l->tail = NULL;
	l->cursor = NULL;

	return l;
}

linked_list_t * linked_list_copy_ (linked_list_t * src, size_t size) {
	linked_list_t * trg = linked_list_create ();

	list_node_t * saved_cursor = src->cursor;

	linked_list_stop_iteration (src);

	void * p_ptr = NULL;

	while ((p_ptr = linked_list_next_ (src)) != NULL) {
		void * copy = x_malloc (size);
		memcpy (copy, p_ptr, size);
		linked_list_append (trg, copy);
	}

	src->cursor = saved_cursor;

	return trg;
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

list_node_t * linked_list_insert_after (linked_list_t * list, list_node_t * after, void * payload) {
	list_node_t * n = x_malloc (sizeof (list_node_t));

	n->payload = payload;
	n->next = after->next;

	after->next = n;

	if (list->tail == after)
		list->tail = n;

	return n;
}

void linked_list_add_sorted (linked_list_t * list, void * payload, int (*comparator) (const void *, const void *), bool unique) {
	list_node_t * prev = NULL;
	list_node_t * where = list->head;

	while (where) {
		int cmp = comparator (where->payload, payload);

		if (cmp == 0 && unique) {
			free (payload);
			return;
		} else if (cmp <= 0) {
			prev = where;
			where = where->next;
		} else
			break;
	}

	if (prev == NULL)
		linked_list_add (list, payload);
	else
		linked_list_insert_after (list, prev, payload);
}

list_node_t * linked_list_append (linked_list_t * list, void * payload) {
	if (list->tail)
		return linked_list_insert_after (list, list->tail, payload);
	else
		return linked_list_add (list, payload);
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

void linked_list_free_ (linked_list_t * list, bool free_payload) {
	if (!list)
		return;

	while (list->head) {
		list_node_t * t = list->head->next;

		if (free_payload)
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

void linked_list_delete (linked_list_t * list, void * payload) {
	list_node_t * node = list->head;
	list_node_t * prev = NULL;

	while (node) {
		if (node->payload == payload)
			break;

		prev = node;
		node = node->next;
	}

	if (list->cursor == node)
		list->cursor = node->next;

	if (list->tail == node)
		list->tail = prev;

	if (prev)
		prev->next = node->next;
	else
		list->head = list->head->next;

	free (node->payload);
	free (node);
}

long linked_list_sum_int (linked_list_t * list) {
	long sum = 0;

	int * i_ptr = NULL;

	while ((i_ptr = linked_list_next (list, int)) != NULL)
		sum += *i_ptr;

	return sum;
}

long linked_list_sum_long (linked_list_t * list) {
	long sum = 0;

	long * l_ptr = NULL;

	while ((l_ptr = linked_list_next (list, long)) != NULL)
		sum += *l_ptr;

	return sum;
}
