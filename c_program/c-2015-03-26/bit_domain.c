#include <stdio.h>

union {
	struct {
#if 0
		unsigned int a : 1;
		unsigned int b : 2;
		unsigned int c : 3;
		unsigned int d : 1;
#else
		int a : 1;
		int b : 2;
		int c : 3;
		int d : 1;
#endif
	} xxx;
	unsigned int yyy;
} foo;

int main(void)
{
	foo.yyy = 055;
	printf("%d %d %d %d\n", foo.xxx.a, foo.xxx.b, foo.xxx.c, foo.xxx.d);

	return 0;
}
