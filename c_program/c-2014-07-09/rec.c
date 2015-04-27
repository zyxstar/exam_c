#include <stdio.h>

int fact(int n)
{
	if (n == 1) {
		return 1;
	}
	return n * fact(n - 1);
}

int fb(int n)
{
	if (n == 1 || n == 2) {
		return 1;
	}

	return fb(n - 1) + fb(n - 2);
}

int main(void)
{
	printf("%d\n", fb(11));

	return 0;
}
