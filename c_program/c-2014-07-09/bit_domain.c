#include <stdio.h>

union {
	struct {
		unsigned int a : 1;
		unsigned int b : 2;
		unsigned int c : 1;
	} b;
	int yyy;
} xxx;

int main(void)
{
	xxx.yyy = 0x9c;

	printf("%d %d %d\n", xxx.b.a, xxx.b.b, xxx.b.c);

	return 0;
}
