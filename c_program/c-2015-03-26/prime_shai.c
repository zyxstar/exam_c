#include <stdio.h>

int main(void)
{
	int arr[1001] = {};
	int i, j;

	for (i = 2; i < 500; i++) {
		if (arr[i] == 1) {
			continue;
		}

		for (j = i + i; j < 1001; j += i) {
			arr[j] = 1;
		}
	}

	for (i = 2; i < 1001; i++) {
		if (arr[i] == 0) {
			printf("%d ", i);
		}
	}
	printf("\n");

	return 0;
}
