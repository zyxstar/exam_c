#include <stdio.h>

struct __attribute__ ((__packed__)) foo {
	int a;
	double d;
	char c;
};

struct bar {
	int a;
	double d;
	char c;
};

int main(void)
{
	printf("%d\n", sizeof(struct foo));
	printf("%d\n", sizeof(struct bar));

	return 0;
}
