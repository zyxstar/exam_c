#include <stdio.h>

struct foo {
	int a;
	char c;
	int b;
	char cc;
} __attribute__ ((__packed__));

int main(void)
{
	int a;

	printf("%d %d %d\n", sizeof(int), sizeof(a), sizeof(double));
	printf("sizeof(struct foo) = %d\n", sizeof(struct foo));

	return 0;
}
