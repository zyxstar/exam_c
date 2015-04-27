#include <stdio.h>

int main(void)
{
	int arr[] = {11,22,33,44,55,66};
	int *p;
	int (*ap)[6] = &arr;
	int i, j;

	p = (int *)ap;

	for (i = 0; i < 6; i++) {
		printf("%d ", p[i]);
	}
	printf("\n");

	return 0;
}


