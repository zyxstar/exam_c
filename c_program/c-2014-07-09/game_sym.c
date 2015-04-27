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

int main(void)
{
	int (*op_arr[4])(int, int) = {add, sub, mul, div};
	int sym_arr[4] = {'+', '-', '*', '/'};
	int i, j;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (op_arr[j](op_arr[i](6, 5), 3) == 27) {
				printf("(6 %c 5) %c 3 = 27\n", sym_arr[i], sym_arr[j]);
			}
		}
	}

	return 0;
}
