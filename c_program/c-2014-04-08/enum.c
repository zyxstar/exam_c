#include <stdio.h>

enum foo {AAA = -4, BBB, CCC = 100, DDD, EEE};

enum {CH, MATH, PHY, EN, NUM};

int main(void)
{
	enum foo a;

	int arr[NUM];

	printf("%d, %d, %d, %d, %d\n", AAA, BBB, CCC, DDD, EEE);

	return 0;
}
