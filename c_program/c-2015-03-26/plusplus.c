#include <stdio.h>

int main(void)
{
	int a = 5;
	int b;

	a = a + 1;
	a++; ++a;

	b = a++; b = ++a;
	b = a++ + ++a;
	a = a++; a--;
}
