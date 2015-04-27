#include <stdlib.h>
#include <string.h>

#include "llist.h"

#if 0
struct llist_node_st {
	void *data;
	struct llist_node_st *prev;
	struct llist_node_st *next;
};
typedef struct {
	int size;
	struct llist_node_st head;
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
	new->head.next = new->head.prev = &new->head;

	return new;
}

void llist_destroy(LLIST *ptr)
{
	struct llist_node_st *cur, *next;

	for (cur = ptr->head.next; cur != &ptr->head; cur = next) {
		next = cur->next;
		free(cur->data);
		free(cur);
	}
	free(ptr);
}

int llist_add(LLIST *ptr, const void *data, int dir)
{
	struct llist_node_st *newnode;

	newnode = malloc(sizeof(*newnode));
	if (newnode == NULL) {
		goto malloc_node_err;
	}
	newnode->data = malloc(ptr->size);
	if (newnode->data == NULL) {
		goto malloc_data_err;
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


	free(newnode->data);
malloc_data_err:
	free(newnode);
malloc_node_err:
	return -1;
}
void *llist_fetch(LLIST *ptr , const void *key, llist_cmp *cmp)
{
	struct llist_node_st *cur;
    for (cur = ptr->head.next; cur != &ptr->head; cur = cur->next) {
        if (cmp(key, cur->data) == 0) {
            cur->next->prev = cur->prev;
            cur->prev->next = cur->next;
			void * a=cur->data;
            free(cur);
            return a;
        }   
     }

    return NULL;
}

void llist_delet(LLIST *ptr, const void *key, llist_cmp *cmp)
{
	struct llist_node_st *cur;

	for (cur = ptr->head.next; cur != &ptr->head; cur = cur->next) {
		if (cmp(key, cur->data) == 0) {
			cur->next->prev = cur->prev;
			cur->prev->next = cur->next;
			free(cur->data);
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
