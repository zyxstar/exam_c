#include <stdio.h>

int main(void)
{
	int arr[] = {11,22,33,44};
	int brr[8] = {[6] = 11, [2] = 33};
	int i;

	for (i = 0; i < 8; i++) {
		printf("%d ", brr[i]);
	}
	printf("\n");

	return 0;
}
