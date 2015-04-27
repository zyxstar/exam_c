#include <stdlib.h>
#include <string.h>

#include "llist.h"

LLIST *llist_creat(int size)
{
	LLIST *new;

	new = malloc(sizeof(*new));
	if (new == NULL) {
		return NULL;
	}

	new->size = size;
	new->head.next = new->head.prev = &new->head;

	return new;
}

void llist_destroy(LLIST *ptr)
{
	struct llist_node_st *cur, *next;

	for (cur = ptr->head.next; cur != &ptr->head; cur = next) {
		next = cur->next;
		free(cur);
	}
	free(ptr);
}

int llist_add(LLIST *ptr, const void *data, int dir)
{
	struct llist_node_st *newnode;

	newnode = malloc(sizeof(*newnode) + ptr->size);
	if (newnode == NULL) {
		goto malloc_node_err;
	}

	memcpy(newnode->data, data, ptr->size);

	if (dir == LLIST_ADD_FORWARD) {
		newnode->next = ptr->head.next;
		newnode->prev = &ptr->head;
	} else {
		newnode->next = &ptr->head;
		newnode->prev = ptr->head.prev;
	}

	newnode->next->prev = newnode;
	newnode->prev->next = newnode;

	return 0;


	free(newnode);
malloc_node_err:
	return -1;
}

void llist_delet(LLIST *ptr, const void *key, llist_cmp *cmp)
{
	struct llist_node_st *cur;

	for (cur = ptr->head.next; cur != &ptr->head; cur = cur->next) {
		if (cmp(key, cur->data) == 0) {
			cur->next->prev = cur->prev;
			cur->prev->next = cur->next;
			free(cur);
			return;
		}
	}
}

void *llist_find(LLIST *ptr, const void *key, llist_cmp *cmp)
{
	struct llist_node_st *cur;

	for (cur = ptr->head.next; cur != &ptr->head; cur = cur->next) {
		if (cmp(key, cur->data) == 0) {
			return cur->data;
		}
	}
	return NULL;
}

void llist_travel(LLIST *ptr, llist_op *op)
{
	struct llist_node_st *cur;

	for (cur = ptr->head.next; cur != &ptr->head; cur = cur->next) {
		op(cur->data);
	}
}

int llist_fetch(LLIST *ptr, const void *key, llist_cmp *cmp, void *data)
{
	struct llist_node_st *cur, *save;

	for (cur = ptr->head.next; cur != &ptr->head; cur = cur->next) {
		if (cmp(key, cur->data) == 0) {
			memcpy(data, cur->data, ptr->size);

			save = cur;
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
			free(cur);
			return 0;
		}
	}
	return -1;
}

/* tmp */
int llist_get_num(LLIST *ptr)
{
	int i;
	struct llist_node_st *cur;

	for (i = 0, cur = ptr->head.next; cur != &ptr->head; cur = cur->next, i++)
		;

	return i;
}
