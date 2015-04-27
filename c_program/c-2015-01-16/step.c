#include <stdio.h>

#define STACK_NR 20

static int stack[STACK_NR];
static int ind;

static void push(int data)
{
	stack[ind++] = data;
}

static int pop(void)
{
	return stack[--ind];
}

static void travel(void)
{
	int i;

	for (i = 0; i < ind; i++) {
		printf("%d ", stack[i]);
	}
	printf("\n");
}

int step(int n)
{
	int i;
	int sum = 0;

	if (n == 0) {
		travel();
		return 1;
	}
	if (n < 0) {
		return 0;
	}

	for (i = 1; i <= 3; i++) {
		push(i);
		sum += step(n - i);
		pop();
	}

	return sum;
}

int main(void)
{
	int sum;

	sum = step(5);
	printf("sum = %d\n", sum);

	return 0;
}
