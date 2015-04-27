#include <stdio.h>

void sort(int arr[], int num)
{
	int i, j;
	int tmp;
	int flag;

	for (i = 0; i < num - 1; i++) {
		flag = 0;
		for (j = 0; j < num - 1 - i; j++) {
			if (arr[j] > arr[j + 1]) {
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
				flag = 1;
			}
		}
		if (flag == 0) {
			break;
		}
	}
}

int main(void)
{
	int arr[9] = {3,6,2,8,1,9,4,5,7};
	int i;

	sort(arr, 9);

	for (i = 0; i < 9; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	return 0;
}
