#include <stdio.h>

#define STACK_NR 4

static int stack[STACK_NR];
static int ind;

static int is_empty(void)
{
	return !ind;
}

static int is_full(void)
{
	return ind >= STACK_NR;
}

int push(int data)
{
	if (is_full()) {
		return -1;
	}

	stack[ind++] = data;
	return 0;
}

int pop(int *data)
{
	if (is_empty()) {
		return -1;
	}

	*data = stack[--ind];
	return 0;
}

int main(void)
{
	int arr[] = {3,2,1,6,7};
	int i;
	int data;
	int ret;

	for (i = 0; i < sizeof(arr) / sizeof(*arr); i++) {
		ret = push(arr[i]);
		if (ret == -1) {
			printf("stack full.\n");
			break;
		}
	}

	while (1) {
		ret = pop(&data);
		if (ret == -1) {
			printf("stack empty.\n");
			break;
		}
		printf("%d ", data);
	}
	printf("\n");

	return 0;
}
