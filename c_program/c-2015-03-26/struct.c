#include <stdio.h>

struct point {
	int x;
	int y;
};

struct {
	int xxx;
	int yyy;
} aaa, bbb;

struct __attribute__ ((__packed__)) tmp {
	int tmp;
	char c;
} tmp, aa;

int main(void)
{
	//struct point a = {3,6}, b;
	struct point a = {.y = 6,}, b;
	struct point *p = &a;

	//a = (struct point){3,6};
	b = a;
	a.x = 10;
	a.y = a.x + 6;

	printf("sizeof(tmp) = %d, sizeof(struct tmp) = %d\n", sizeof(tmp), sizeof(struct tmp));
	printf("sizeof(a) = %d, sizeof(struct point) = %d\n", sizeof(a), sizeof(struct point));
	printf("a.x = %d, a.y = %d\n", a.x, a.y);
	printf("b.x = %d, b.y = %d\n", b.x, b.y);
	//(*p).x += 23;
	p->x += 23;
	printf("a.x = %d, a.y = %d\n", a.x, a.y);
	printf("(*p).x = %d, (*p).y = %d\n", (*p).x, (*p).y);

	return 0;
}
