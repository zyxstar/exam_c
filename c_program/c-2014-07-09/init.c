#include <stdio.h>

struct bar {
	int a;
	int b;
	int c;
};

void foo(void)
{
	int i = 6;

	//int arr[8] = {11, 22, 33,};
	int arr[8] = {[5] = 77, [2] = 66, };

	//struct bar xx = {44, 55, };
	struct bar xx = {.b = 44, };

	for (i = 0; i < 8; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	printf("%d %d %d\n", xx.a, xx.b, xx.c);
}

int main(void)
{
	foo();
	return 0;
}
