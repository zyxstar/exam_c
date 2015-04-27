#include <stdio.h>

void sort(int arr[], int num)
{
	int i, j;
	int tmp;

	for (j = 0; j < num - 1; j++) {
		for (i = 0; i < num - 1 - j; i++) {
			if (arr[i] > arr[i + 1]) {
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
			}
		}
	}
}

void sort_homework(int arr[], int num)
{
	int i, j;
	int tmp;
	int sorted;

	for (j = 0; j < num - 1; j++) {
		sorted = 1;
		for (i = 0; i < num - 1 - j; i++) {
			if (arr[i] > arr[i + 1]) {
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
				sorted = 0;
			}
		}
		if (sorted) {
			break;
		}
	}
	printf("j = %d\n", j);
}

int main(void)
{
	//int arr[9] = {5,3,9,8,7,2,4,1,6};
	int arr[9] = {1,2,3,4,9,5,6,7,8};
	int i;

	sort_homework(arr, 9);
	for (i = 0; i < 9; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	return 0;
}
