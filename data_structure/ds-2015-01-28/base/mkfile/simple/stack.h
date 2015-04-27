#ifndef HS_STACK_H
#define HS_STACK_H

#include "llist.h"

typedef LLIST STACK;

STACK *stack_creat(int size);

void stack_destroy(STACK *);

int stack_push(STACK *, const void *);

int stack_pop(STACK *, void *);

#endif	/* HS_STACK_H */
