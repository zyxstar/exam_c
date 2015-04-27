#include <stdio.h>

int main(void)
{
	int arr[4] = {11,22,33};
	int (*p)[4];
	int i;

	p = &arr;

	for (i = 0; i < 4; i++) {
		printf("%d ", (*p)[i]);
	}
	printf("\n");

	return 0;
}
