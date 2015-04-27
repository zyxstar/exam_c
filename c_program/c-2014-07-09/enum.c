#include <stdio.h>

enum xxx {AAA = -1, BBB, CCC = 123, DDD};

enum {CH, MATH, PHY, EN, NUM};

int main(void)
{
	int a;
	enum xxx b;
	int arr[NUM];

	a = BBB;

	printf("a = %d\n", a);
	printf("%d %d %d %d\n", AAA, BBB, CCC, DDD);

	return 0;
}
