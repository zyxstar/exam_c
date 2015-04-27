#include <stdio.h>

int main(void)
{
	int arr[] = {8,2,4,1,9,5,7,6,3};
	int tmp;
	int i, j;

	for (j = 0; j < 8; j++) {
		for (i = 0; i < 8 - j; i++) {
			if (arr[i] > arr[i + 1]) {
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
			}
		}
	}

	for (i = 0; i < 9; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	return 0;
}
