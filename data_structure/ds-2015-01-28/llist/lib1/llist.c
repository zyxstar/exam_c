#include <stdlib.h>
#include <string.h>

#include "llist.h"

#if 0
typedef int llist_cmp(const void *, const void *);
typedef void llist_op(const void *, void *);
struct node_st {
	void *data;
	struct node_st *prev;
	struct node_st *next;
};
typedef struct {
	struct node_st head;
	int size;
} LLIST;
#endif

LLIST *llist_creat(int size)
{
	LLIST *new;

	new = malloc(sizeof(*new));
	if (new == NULL) {
		return NULL;
	}

	new->size = size;
	new->head.data = NULL;
	new->head.next = new->head.prev = &new->head;

	return new;
}

void llist_destroy(LLIST *ptr)
{
	struct node_st *cur, *next;

	for (cur = ptr->head.next; cur != &ptr->head; cur = next) {
		next = cur->next;
		free(cur->data);
		free(cur);
	}
	free(ptr);
}

int llist_insert(LLIST *ptr, const void *data, int dir)
{
	struct node_st *node;

	node = malloc(sizeof(*node));
	if (node == NULL) {
		return -1;
	}
	node->data = malloc(ptr->size);
	if (node->data == NULL) {
		free(node);
		return -1;
	}

	memcpy(node->data, data, ptr->size);
	if (dir == DIR_FRONT) {
		node->next = ptr->head.next;
		node->prev = &ptr->head;
	} else {
		node->next = &ptr->head;
		node->prev = ptr->head.prev;
	}
	node->next->prev = node;
	node->prev->next = node;

	return 0;
}

void llist_delet(LLIST *ptr, const void *key, llist_cmp *cmp)
{
	struct node_st *cur;

	for (cur = ptr->head.next; cur != &ptr->head; cur = cur->next) {
		if (cmp(key, cur->data) == 0) {
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;

			free(cur->data);
			free(cur);
			return;
		}
        }
}

void *llist_search(LLIST *ptr, const void *key, llist_cmp *cmp)
{
	struct node_st *cur;

        for (cur = ptr->head.next; cur != &ptr->head; cur = cur->next) {
		if (cmp(key, cur->data) == 0) {
			return cur->data;
		}
        }
	return NULL;
}

int llist_fetch(LLIST *ptr, void *data, const void *key, llist_cmp *cmp)
{
	struct node_st *cur;

	for (cur = ptr->head.next; cur != &ptr->head; cur = cur->next) {
		if (cmp(key, cur->data) == 0) {
			memcpy(data, cur->data, ptr->size);

			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;

			free(cur->data);
			free(cur);
			return 0;
		}
        }

	return -1;
}

void llist_travel(LLIST *ptr, llist_op *op, void *arg)
{
	struct node_st *cur;

	for (cur = ptr->head.next; cur != &ptr->head; cur = cur->next) {
		op(cur->data, arg);
	}
}
