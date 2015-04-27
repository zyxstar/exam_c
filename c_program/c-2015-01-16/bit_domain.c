#include <stdio.h>

struct foo {
	unsigned int a : 1;
	unsigned int b : 3;
	unsigned int c : 2;
	unsigned int d : 4;
};
union {
	struct foo f;
	unsigned int ch;
} bar;
int main(void)
{
	//bar.ch = 53;
	bar.ch = 0x535;
	printf("%d %d %d %d\n", bar.f.a, bar.f.b, bar.f.c, bar.f.d);
	//bar.f.b >>= 1;
	bar.f.b = bar.f.b >> 1;
	printf("%d %d %d %d\n", bar.f.a, bar.f.b, bar.f.c, bar.f.d);

	return 0;
}
