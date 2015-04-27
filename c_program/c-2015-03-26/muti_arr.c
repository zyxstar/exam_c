#include <stdio.h>

int main(void)
{
	int arr[3][4] = {{11,22,33}, {44}, {55,66,}};
	int brr[3][4] = {111,222,333,444,555,666};
	int i, j;

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 4; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 4; j++) {
			printf("%d ", brr[i][j]);
		}
		printf("\n");
	}

	return 0;
}
