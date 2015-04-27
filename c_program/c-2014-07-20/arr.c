#include <stdio.h>

#define N 6

void foo(int arr[N])
{
	int i;

	for (i = 0; i < N; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void foo(int arr[], int n)
{
	int i;

        for (i = 0; i < n; i++) {
                printf("%d ", arr[i]);
        }
        printf("\n");
}

int main(void)
{
	int arr[M][N];
	int arr[N] = {11,22,33,44};

	foo(arr, N);

	return 0;
}
