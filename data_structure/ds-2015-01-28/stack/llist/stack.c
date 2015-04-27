#include <stdlib.h>

#include "stack.h"

STACK *stack_creat(int size)
{
	return llist_creat(size);
}

void stack_destroy(STACK *ptr)
{
	llist_destroy(ptr);
}

int stack_push(STACK *ptr, const void *data)
{
	return llist_insert(ptr, data, DIR_FRONT);
}

static int always_match(const void *d1, const void *d2)
{
	return 0;
}

int stack_pop(STACK *ptr, void *data)
{
	return llist_fetch(ptr, data, NULL, always_match);
}
