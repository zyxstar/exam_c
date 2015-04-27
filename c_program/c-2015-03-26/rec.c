#include <stdio.h>

int jc(int n)
{
	if (n == 1) {
		return 1;
	}
	return n * jc(n - 1);
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
	int n = 6;

	printf("%d\n", fb(n));

	return 0;
}
