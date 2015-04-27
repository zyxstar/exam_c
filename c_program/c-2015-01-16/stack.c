#include "stack.h"

#define STACK_NR 5

static int stack[STACK_NR];
static int ind;

static int is_full(void)
{
	if (ind == STACK_NR) {
		return 1;
	}
	return 0;

	return !(ind - STACK_NR);
}

static int is_empty(void)
{
	if (ind == 0) {
		return 1;
	}
	return 0;

	return !ind;
}

int push(int data)
{
	if (is_full()) {
		return -1;
	}

	stack[ind] = data;
	ind++;

	return 0;
}

int pop(int *data)
{
	if (is_empty()) {
		return -1;
	}

	ind--;
	*data = stack[ind];

	return 0;
}
