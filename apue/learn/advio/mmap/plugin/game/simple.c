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

/* (2 [] 2) [] 9 = 13 */
int main(void)
{
	int (*func[4])(int, int) = {add, sub, mul, div};
	char sym[] = "+-*/";
	int i, j;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (func[j](func[i](2, 2), 9) == 13) {
				printf("(2 %c 2) %c 9 = 13\n", sym[i], sym[j]);
			}
		}
	}

	return 0;
}
