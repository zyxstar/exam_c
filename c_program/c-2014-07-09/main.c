#include <stdio.h>

#include "stack.h"

int main(void)
{
	int arr[] = {3,2,1,6,7};
	int i;
	int ret;
	int data;

	for (i = 0; i < 5; i++) {
		ret = push(arr[i]);
		if (ret == -1) {
			printf("stack full, i = %d\n", i);
			break;
		}
	}

	for (i = 0; i < 5; i++) {
		ret = pop(&data);
		if (ret == -1) {
			printf("stack empty, i = %d\n", i);
			break;
		}
		printf("%d ", data);
	}
	printf("\n");

	return 0;
}
