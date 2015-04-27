#include <stdio.h>

struct uuuu {
	int uuuu;
} uuuu;

struct point {
	int x;
	int y;
};

struct foo {
	int a;
	struct point dir;
	char str[32];
} xxx, yyy;

void bar(struct point aa, struct point *bb)
{
	printf("in bar(): (%d, %d), (%d, %d)\n", aa.x, aa.y, (*bb).x, (*bb).y);

	aa.x = 123, aa.y = 456;
	(*bb).x = 1234, bb->y = 5678;
}

int main(void)
{
	struct point a, b;

	a.x = 5;
	a.y = 6;

	bar(a, &b);

	printf("a = (%d, %d)\n", a.x, a.y);

	printf("b = (%d, %d)\n", b.x, b.y);
	b = a;
	printf("b = (%d, %d)\n", b.x, b.y);

	struct foo aa = {32167, "hello"};
	struct foo bb = {.str = "qn"};

	printf("%d, %s\n", aa.a, aa.str);

	printf("%d, %s\n", bb.a, bb.str);
	bb = aa;
	printf("%d, %s\n", bb.a, bb.str);

	return 0;
}
