#include <stddef.h>

#include "heap.h"

#define MIN_SIZE          (sizeof(char *) * 3)
#define MAX_ALIGN_SIZE    (sizeof(int))

struct node_st {
	struct node_st *prev;
	struct node_st *next;
	char *end;
};

HEAP *heap_init(void *ptr, int size)
{
	struct node_st *head, *node;

	head = ptr;
	node = head + 1;

	head->end = (char *)node;
	head->prev = head->next = node;

	node->end = (char *)ptr + size;
	node->prev = node->next = head;

	return head;
}

void heap_destroy(HEAP *list)
{
	/* do nothing */
}

static int size2alloc(int size)
{
	size += sizeof(char *);
	size = (size > MIN_SIZE ? size : MIN_SIZE);

	//size = (size + MAX_ALIGN_SIZE - 1) / MAX_ALIGN_SIZE * MAX_ALIGN_SIZE;
	size = (size + MAX_ALIGN_SIZE - 1) & ~(MAX_ALIGN_SIZE - 1);
}

static int node_size(struct node_st *node)
{
	return node->end - (char *)node;
}

static struct node_st *find_node(struct node_st *head, int size)
{
	struct node_st *cur;

	for (cur = head->next; cur != head; cur = cur->next) {
		if (node_size(cur) >= size) {
			return cur;
		}
	}
	return head;
}

static void node2mem(struct node_st *node, int size, char **start, char **end)
{
	*end = node->end;

	if (node_size(node) - size > MIN_SIZE) {
		*start = node->end - size;
		node->end = *start;
		return;
	}

	node->prev->next = node->next;
	node->next->prev = node->prev;
	*start = (char *)node;
}

static void *mem2user(char *start, char *end)
{
	char **desc = (char **)start;
	*desc = end;
	return desc + 1;
}

void *heap_alloc(HEAP *list, int size)
{
	struct node_st *head = list, *node;
	char *start, *end;

	size = size2alloc(size);

	node = find_node(head, size);
	if (node == head) {
		return NULL;
	}

	node2mem(node, size, &start, &end);

	return mem2user(start, end);
}

static struct node_st *user2node(void *ptr)
{
	struct node_st *node;
	char **desc;

	desc = ptr;
	desc--;

	node = (struct node_st *)desc;
	node->end = *desc;

	return node;
}

void heap_free(HEAP *list, void *ptr)
{
	struct node_st *head = list, *node;

	node = user2node(ptr);

	node->next = head->next;
	node->prev = head;
	node->prev->next = node;
	node->next->prev = node;

	//merge(head, node);
}
