#include <stdio.h>

#include "stack.h"

#if 0
int step(int n)
{
	int i;
	int total;
	int tmp;

	if (n == 0) {
		travel();
		return 1;
	}
	if (n < 0) {
		return 0;
	}

	total = 0;
	for (i = 1; i <= 3; i++) {
		push(i);
		total += step(n - i);
		pop(&tmp);
	}

	return total;
}
#else
static int step__(int n, int stack[], int ind)
{
	int i;
	int total;
	int tmp;

	if (n == 0) {
		//travel();
		for (i = 0; i < ind; i++) {
			printf("%d ", stack[i]);
		}
		printf("\n");
		return 1;
	}
	if (n < 0) {
		return 0;
	}

	total = 0;
	for (i = 1; i <= 3; i++) {
		//push(i);
		stack[ind] = i;
		total += step__(n - i, stack, ind + 1);
	}

	return total;
}

#define STACK_NR 32
int step(int n)
{
	int stack[STACK_NR];
	return step__(n, stack, 0);
}
#endif

int main(void)
{
	int ret;

	ret = step(7);

	printf("total: %d\n", ret);

	return 0;
}
