#include <stdio.h>

inline int min(int a, int b)
{
	return a < b ? a : b;
}

int main(void)
{
	printf("%d\n", min(3, 5));

	return 0;
}
