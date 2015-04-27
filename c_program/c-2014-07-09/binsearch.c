#include <stdio.h>

int main(void)
{
	int arr[10] = {1,3,5,7,9,11,15,17,19,21};
	int data = 2;
	int ind;

	int start, end, mid;

	ind = -1;
	start = 0; end = 9;
	while (start <= end) {
		mid = (start + end) / 2;
		if (data == arr[mid]) {
			ind = mid;
			break;
		}
		if (data < arr[mid]) {
			end = mid - 1;
		} else {
			start = mid + 1;
		}
	}

	printf("ind = %d\n", ind);

	return 0;
}
