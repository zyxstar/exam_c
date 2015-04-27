#include <stdlib.h>

#include "queue.h"

QUEUE *queue_creat(int size)
{
	return llist_creat(size);
}

void queue_destroy(QUEUE *ptr)
{
	llist_destroy(ptr);
}

int queue_enq(QUEUE *ptr, const void *data)
{
	return llist_insert(ptr, data, DIR_BACK);
}

static int always_match(const void *d1, const void *d2)
{
	return 0;
}

int queue_deq(QUEUE *ptr, void *data)
{
	return llist_fetch(ptr, data, NULL, always_match);
}
