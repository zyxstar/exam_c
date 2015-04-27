#include <stdio.h>

int add(int a, int b)
{
	return a + b;
}

int sub(int a, int b)
{
	return a - b;
}

int mul(int a, int b)
{
	return a * b;
}

int div(int a, int b)
{
	return a / b;
}

/* 4 [] 8 = 32 */
int main(void)
{
	//int (*arr[])(int, int) = {add, sub, mul, div};

	//typedef int func_t(int, int);
	//func_t *arr[] = {add, sub, mul, div};

	typedef int (*funcp_t)(int, int);
	funcp_t arr[] = {add, sub, mul, div};

	int sym[] = {'+', '-', '*', '/'};
	int i;

	for (i = 0; i < sizeof(arr) / sizeof(*arr); i++) {
		if (arr[i](4, 8) == 32) {
			printf("4 %c 8 = 32\n", sym[i]);
		}
	}

	return 0;
}
