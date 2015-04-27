#include <stdlib.h>
#include <string.h>

#include "llist.h"

#if 0
typedef int llist_cmp(const void *, const void *);
typedef void llist_op(void *, void *priv);
struct llist_node_st {
	void *data;
	struct llist_node_st *next;
	struct llist_node_st *prev;
};
typedef struct {
	struct llist_node_st head;
	int size;
	/* home works */
	int num;
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
	new->head.next = &new->head;
	new->head.prev = &new->head;

	return new;
}

void llist_destroy(LLIST *ptr)
{
	/* fix me */
	return;
}

int llist_insert(LLIST *ptr, const void *data)
{
	struct llist_node_st *newnode;

	newnode = malloc(sizeof(*newnode) + ptr->size);
	if (newnode == NULL) {
		return -1;
	}

	memcpy(newnode->data, data, ptr->size);

	newnode->prev = &ptr->head;
	newnode->next = ptr->head.next;
	newnode->prev->next = newnode;
	newnode->next->prev = newnode;

	return 0;
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

int llist_fetch(LLIST *ptr, const void *key, llist_cmp *cmp, void *data)
{
	struct llist_node_st *cur;

        for (cur = ptr->head.next; cur != &ptr->head; cur = cur->next) {
		if (cmp(key, cur->data) == 0) {
			memcpy(data, cur->data, ptr->size);
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
			free(cur);
			return 0;
		}
        }
	return -1;
}

void llist_travel(LLIST *ptr, llist_op *op, void *priv)
{
	struct llist_node_st *cur;

	for (cur = ptr->head.next; cur != &ptr->head; cur = cur->next) {
		op(cur->data, priv);
	}
}

int llist_get_num(LLIST *ptr)
{
	struct llist_node_st *cur;
	int sum = 0;

	for (cur = ptr->head.next; cur != &ptr->head; cur = cur->next) {
		sum++;
	}

	return sum;
}
