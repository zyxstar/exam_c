#ifndef STU_STACK_H_
#define STU_STACK_H_

#include "llist.h"

typedef LLIST QUEUE;

QUEUE *queue_create(int);
void queue_destroy(QUEUE *);
int queue_enq(QUEUE *, const void *);
int queue_deq(QUEUE *, void *);

#endif	/* STU_STACK_H_ */
