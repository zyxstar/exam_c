#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

static int  always_zero(const void *fp1, const void *fp2)
{
	return 0;
}

QUEUE *queue_create(int size)
{
	return llist_creat(size);
}

void queue_destroy(QUEUE *queue)
{
	llist_destroy(queue);
}

int queue_enq(QUEUE *queue, const void *data)
{
	return llist_insert_tail(queue, data);
}


int queue_deq(QUEUE *queue, void *data)
{
	 return llist_fetch(queue,NULL,always_zero,data);
}

