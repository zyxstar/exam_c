#include <stdio.h>

#include "stack.h"

int step(int n)
{
	int i;
	int sum = 0;
	int data;

	if (n == 0) {
		travel();
		return 1;
	} else if (n < 0) {
		return 0;
	}

	for (i = 1; i <= 3; i++) {
		push(i);	/* if error */
		sum += step(n - i);
		pop(&data);
	}

	return sum;
}

int main(void)
{
	printf("sum = %d\n", step(9));

	return 0;
}
