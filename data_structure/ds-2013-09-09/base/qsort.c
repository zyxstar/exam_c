#include <stdio.h>
#include <stdlib.h>

int int_cmp(const void *data1, const void *data2)
{
	const int *d1 = data1;
	const int *d2 = data2;

	return *d1 - *d2;
}

int main(void)
{
	int arr[] = {3,2,1,6,7,9,5,4,8};
	int i;
	int num;

	num = sizeof(arr) / sizeof(*arr);
	qsort(arr, num, sizeof(*arr), int_cmp);
	for (i = 0; i < num; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	return 0;
}
