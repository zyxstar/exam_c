#include <stdio.h>

int binsearch(int arr[], int num, int data)
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
	int arr[] = {1,3,5,7,9,11,13,15,17,19};
	int ind;

	ind = binsearch(arr, 10, -1);
	printf("ind = %d\n", ind);

	return 0;
}
