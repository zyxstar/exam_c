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

/* (3 [] 4) [] 17 = 29 */
int main(void)
{
	int (*func_arr[4])(int, int) = {add, sub, mul, div};
	char symbol_arr[5] = "+-*/";
	int i, j;
	int val;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			val = func_arr[j](func_arr[i](3, 4), 17);
			if (val == 29) {
				printf("(3 %c 4) %c 17 = 29\n", symbol_arr[i], symbol_arr[j]);
			}
		}
	}

	return 0;
}
