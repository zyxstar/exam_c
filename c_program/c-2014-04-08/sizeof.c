#include <stdio.h>

struct foo {
	int a;
	double b;
	char c0;
	char c1;
} __attribute__ ((__packed__));

union bar {
	int a;
	char c;
	double d;
	char buf[9];
};

int main(void)
{
	double a;

	printf("%d, %d, %d\n", sizeof(int), sizeof(a), sizeof(struct foo));
	printf("sizeof(union bar) = %d\n", sizeof(union bar));

	return 0;
}
