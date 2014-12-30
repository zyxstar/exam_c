#ifndef HS_QUEUE_H
#define HS_QUEUE_H

#include "llist.h"

typedef LLIST QUEUE;

QUEUE *queue_creat(int size);

void queue_destroy(QUEUE *);

int queue_enq(QUEUE *, const void *data);

int queue_deq(QUEUE *, void *data);

#endif
