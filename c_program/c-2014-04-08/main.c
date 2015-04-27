#include <stdio.h>

#include "stack.h"

int main(void)
{
	int arr[] = {11,22, -1, 33,44,55,66,77,88,99};
	int i;
	int ret;
	int val;

	for (i = 0; i < 9; i++) {
		ret = push(arr[i]);
		if (ret == -1) {
			printf("stack full\n");
			break;
		}
	}

	while (1) {
		ret = pop(&val);
		if (ret == -1) {
			printf("stack empty\n");
                        break;
		}
		printf("%d ", val);
	}
	printf("\n");

	return 0;
}
