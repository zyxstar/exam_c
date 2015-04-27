#include <stdio.h>

struct coop {
	int x;
	int y;
	char c;
} __attribute__ ((__packed__));

struct foo {
	char c;
	int a;
};

struct bar {
	struct foo xx;
	int yy;
} __attribute__ ((__packed__));

int main(void)
{
	int a;
	sizeof(a);

	printf("int: %d, double: %d\n", sizeof(int), sizeof(double));
	printf("struct coop: %d\n", sizeof(struct coop));

	return 0;
}
