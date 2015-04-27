#include <stdio.h>

int fact(int n)
{
	if (n == 1) {
		return 1;
	}
	return n * fact(n - 1);
}

int main(void)
{
	int val;

	val = fact(6);

	printf("val = %d\n", val);

	return 0;
}
