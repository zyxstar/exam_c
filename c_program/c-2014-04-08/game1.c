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
	int (*func[4])(int, int) = {add, sub, mul, div};
	char sym[4] = {'+', '-', '*', '/'};
	int i, j;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (func[j](func[i](4, 3), 8) == 56) {
				printf("(4 %c 3) %c 8 = 56\n", sym[i], sym[j]);
			}
		}
	}

	return 0;
}
