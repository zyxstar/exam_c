#include <stdio.h>

#include "stack.h"

int main(void)
{
	int arr[8] = {3,2,-1,6,7,8,9,0};
	int i;
	int ret;
	int data;

	for (i = 0; i < 8; i++) {
		ret = push(arr[i]);
		if (ret == -1) {
			printf("stack full, data = %d\n", arr[i]);
			break;
		}
	}

	for (i = 0; i < 8; i++) {
		ret = pop(&data);
		if (ret == -1) {
			printf("stack empty\n");
			break;
		}

		printf("%d ", data);
	}

	return 0;
}
