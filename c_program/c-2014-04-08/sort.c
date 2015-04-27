#include <stdio.h>

void sort(int *arr, int n)
{
	int tmp;
	int i, j;

	for (j = 0; j < n - 1; j++) {
		for (i = 0; i < n - 1 - j; i++) {
			if (arr[i] > arr[i + 1]) {
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
			}
		}
	}
}

int main(void)
{
	int arr[] = {5,7,9,2,1,3,8,4,6};
	int i;

	sort(arr, 9);
	for (i = 0; i < 9; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	return 0;
}
