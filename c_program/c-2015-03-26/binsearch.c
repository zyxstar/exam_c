#include <stdio.h>

int search(int arr[], int num, int data)
{
	int start, end, mid;

	start = 0; end = num - 1;
	while (start <= end) {
		mid = (start + end) / 2;
		if (data == arr[mid]) {
			return mid;
		}
		if (data < arr[mid]) {
			end = mid - 1;
		} else {
			start = mid + 1;
		}
	}

	return -1;
}

int main(void)
{
	int arr[9] = {11,22,33,44,55,66,77,88,99};
	int ind;

	ind = search(arr, 9, 99);
	printf("ind = %d\n", ind);

	return 0;
}
