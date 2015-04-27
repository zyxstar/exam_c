#include <stdio.h>

int main(void)
{
	char arr[] = {3,5,7,2,4,8,5,4,3,2,6,6,5,4,3,2,5,6,3,6,7};
	//char arr[] = {3,2,1,6,7,5,4,3,2,1};
	int count[11] = {};
	int i, j, ind;

	for (i = 0; i < sizeof(arr) / sizeof(*arr); i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	for (i = 0; i < sizeof(arr) / sizeof(*arr); i++) {
		count[arr[i]]++;
	}

	ind = 0;
	for (i = 0; i < 11; i++) {
		for (j = 0; j < count[i]; j++) {
			arr[ind++] = i;
		}
	}

	for (i = 0; i < sizeof(arr) / sizeof(*arr); i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	return 0;
}
