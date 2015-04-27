#include "stack.h"

#define STACKSIZE 16

static int stack[STACKSIZE];
static int ind;

static int isfull(void)
{
	if (ind == STACKSIZE) {
		return 1;
	}
	return 0;

	return !(ind - STACKSIZE);
}

static int isempty(void)
{
	if (ind == 0) {
		return 1;
	}
	return 0;

	return !ind;
}

int push(int data)
{
	if (isfull()) {
		return -1;
	}

	stack[ind++] = data;
	return 0;
}

int pop(int *data)
{
	if (isempty()) {
		return -1;
	}

	*data = stack[--ind];
	return 0;
}
