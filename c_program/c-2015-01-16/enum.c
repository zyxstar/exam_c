#include <stdio.h>

enum xxx {AAA = -5, BBB, CCC = 100, DDD, EEE};

int main(void)
{
	enum xxx a;

	printf("%d %d %d %d %d\n", AAA, BBB, CCC, DDD, EEE);

	a = 6;
	printf("a = %d\n", a);

	return 0;
}
