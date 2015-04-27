#include <stdlib.h>

#include "heap.h"

struct node_st {
	struct node_st *prev;
	struct node_st *next;
	char *end;
};

#define ALIAN_SIZE      sizeof(long)
#define REMAIN_MIN_SIZE (sizeof(struct node_st) + ALIAN_SIZE)

//#define alian_down(SIZE) ((SIZE) / ALIAN_SIZE * ALIAN_SIZE)
#define alian_down(SIZE) ((SIZE) & ~(ALIAN_SIZE - 1))

#define alian_up(SIZE) alian_down((SIZE) + ALIAN_SIZE - 1)

void *hsheap_init(void *ptr, int size)
{
	struct node_st *head, *first;

	head = ptr;
	first = head + 1;

	head->prev = head->next = first;
	head->end = (char *)first;

	first->prev = first->next = head;
	first->end = (char *)ptr + size;

	return head;
}

void hsheap_destroy(void *handle)
{
	/* nothing */
}

static inline int max(int a, int b)
{
	return a > b ? a : b;
}

static int alloc_size(int size)
{
	size = alian_up(size) + sizeof(char *);
	return max(size, sizeof(struct node_st));
}

static inline int node_size(struct node_st *node)
{
	return node->end - (char *)node;
}

static struct node_st *find_node(struct node_st *head, int size)
{
	struct node_st *cur, *min = head;

	for (cur = head->next; cur != head; cur = cur->next) {
		if (node_size(cur) >= size) {
			if (min == head || node_size(min) > node_size(cur)) {
				min = cur;
			}
		}
	}
	return min;
}

static void *mem2user(void *start, void *end)
{
	char **ptr = start;

	*ptr = end;
	return ptr + 1;
}

void *hsheap_alloc(void *handle, int size)
{
	struct node_st *node;
	char *start, *end;

	size = alloc_size(size);

	node = find_node(handle, size);
	if (node == handle) {
		return NULL;
	}

	end = node->end;
	if (node_size(node) - size < REMAIN_MIN_SIZE) {
		node->prev->next = node->next;
		node->next->prev = node->prev;
		start = (char *)node;
	} else {
		node->end = node->end - size;
		start = node->end;
	}

	return mem2user(start, end);
}

static struct node_st *user2node(void *ptr)
{
	struct node_st *node;
	char **end;

	end = ptr;
	end--;
	node = (struct node_st *)end;
	node->end = *end;
	return node;
}

static void insert(struct node_st *head, struct node_st *node)
{
	struct node_st *cur;

	for (cur = head->next; cur != head; cur = cur->next) {
		if (cur > node) {
			break;
		}
	}

	node->next = cur;
	node->prev = cur->prev;
	node->next->prev = node;
	node->prev->next = node;
}

static void merge(struct node_st *head, struct node_st *node)
{
	/* merge node and next */
	if (node->next != head && node->end == (char *)node->next) {
		node->end = node->next->end;
		node->next = node->next->next;
		node->next->prev = node;
	}

	/* merge node and prev */
	if (node->prev != head && node->prev->end == (char *)node) {
		node->prev->end = node->end;
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
}

void hsheap_free(void *handle, void *ptr)
{
	struct node_st *node;

	node = user2node(ptr);

	insert(handle, node);
	merge(handle, node);
}
