#include <stdio.h>

#define M 3
#define N 4

void foo1(int arr[M][N])
{
	int i, j;

	for (i = 0; i < M; i++) {
		for (j = 0; j < N; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
}

void foo2(int (*arr)[N], int m)
{
	int i, j;

	for (i = 0; i < m; i++) {
		for (j = 0; j < N; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
}

void foo3(int *arr, int m, int n)
{
	int i, j;

	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			printf("%d ", *(arr + i * n + j));
		}
		printf("\n");
	}
}

int main(void)
{
	int arr[M][N] = {
		{11,22,33},
		{44},
		{55,66},
	};

	foo3((int *)arr, M, N);

	return 0;
}
