#include <stdio.h>

void sort(int arr[], int num)
{
	int count[10] = {};
	int i, j;
	int *p;

	for (i = 0; i < num; i++) {
		count[arr[i]]++;
	}

	for (i = 0, p = arr; i < 10; i++) {
		for (j = 0; j < count[i]; j++) {
			*p = i;
			p++;
		}
	}
}

void sort_tmp(int arr[], int num)
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

int main(void)
{
	int arr[] = {7,7,8,1,2,5,3,6,7,3,9,4,3,7,6,5,4,2,8,9,2,5,1,};
	int brr[] = {7,7,8,1,2,5,3,6,7,3,9,4,3,7,6,5,4,2,8,9,2,5,1,};
	int num;
	int i;

	num = sizeof(arr) / sizeof(*arr);
	sort(arr, num);
	sort_tmp(brr, num);
	for (i = 0; i < num; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	for (i = 0; i < num; i++) {
		printf("%d ", brr[i]);
	}
	printf("\n");

	return 0;
}
