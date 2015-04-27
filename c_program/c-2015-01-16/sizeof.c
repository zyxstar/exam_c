#include <stdio.h>

struct foo {
	int a, b;
	char c;
	//double d;
};

int main(void)
{
	int a;

	printf("%d %d\n", sizeof(a), sizeof(int));
	printf("%d\n", sizeof(struct foo));

	return 0;
}
