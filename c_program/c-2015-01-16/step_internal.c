#include <stdio.h>

#define STACK_NR 20

static void travel(int stack[], int ind)
{
	int i;

	for (i = 0; i < ind; i++) {
		printf("%d ", stack[i]);
	}
	printf("\n");
}

static int step_(int n, int stack[], int ind)
{
	int i;
	int sum = 0;

	if (n == 0) {
		travel(stack, ind);
		return 1;
	}

	if (n < 0) {
		return 0;
	}

	for (i = 1; i <= 3; i++) {
		stack[ind] = i;
		sum += step_(n - i, stack, ind + 1);
	}

	return sum;
}

int step(int n)
{
	int stack[STACK_NR];

	return step_(n, stack, 0);
}

int main(void)
{
	int sum;

	sum = step(5);
	printf("sum = %d\n", sum);

	return 0;
}
