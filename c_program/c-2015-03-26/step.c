#include <stdio.h>

#define STACKSIZE 32
static int stack[STACKSIZE];
static int ind;

static void stack_travel(void)
{
	int i;
	for (i = 0; i < ind; i++) {
		printf("%d ", stack[i]);
	}
	printf("\n");
}

static void push(int data)
{
	stack[ind++] = data;
}

static void pop(void)
{
	ind--;
}

int step(int n)
{
	int i;
	int sum;

	if (n == 0) {
		stack_travel();
		return 1;
	}
	if (n < 0) {
		return 0;
	}

	sum = 0;
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

	sum = step(9);
	printf("sum = %d\n", sum);

	return 0;
}
