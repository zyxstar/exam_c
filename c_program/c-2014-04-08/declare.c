#include <stdio.h>

//int add(int abc, int);

int main(void)
{
	int a, b, c;

	b = 3, c = 4;
	a = add(b, (int)4.56);

	printf("a = %d\n", a);

	return 0;
}

int add(int a, int b)
{
	return a + b;
}

