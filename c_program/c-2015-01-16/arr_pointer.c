#include <stdio.h>

int main(void)
{
	int arr[6] = {11,22,33,44,55};
	int (*p)[6];
	int *a;
	int i;

	p = &arr;
	a = arr;

	for (i = 0; i < 6; i++) {
		printf("%d ", (*p)[i]);
	}
	printf("\n");

	for (i = 0; i < 6; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");

	return 0;
}
