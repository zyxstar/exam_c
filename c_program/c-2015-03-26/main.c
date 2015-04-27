#include <stdio.h>

#include "stack.h"

int main(void)
{
	int arr[11] = {3,2,1,6,7,-1,-22,33,44,55,66};
	int i;
	int ret;
	int data;

	for (i = 0; i < 11; i++) {
		ret = push(arr[i]);
		if (ret == -1) {
			printf("stack full, i = %d\n", i);
			break;
		}
	}

	for (i = 0; i < 11; i++) {
		ret = pop(&data);
		if (ret == -1) {
			printf("stack empty\n");
                        break;
		}
		printf("%d ", data);
	}
	printf("\n");

	return 0;
}
