#include <stdio.h>

int main(void)
{
	int arr[3][4] = {{1,}, {2,3,4,}, {5,6}};
	int (*p)[4] = arr;
	int i, j;

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 4; j++) {
			printf("%d ", p[i][j]);
		}
		printf("\n");
	}

	return 0;
}
