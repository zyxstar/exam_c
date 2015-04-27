#include <stdio.h>

struct point {
	int x;
	int y;
};

struct circle {
	struct point cent;
	int r;
} xx;
/* xx.cent.y */

struct {
	int x;
	double y;
} b, c;

int main(void)
{
	struct point a = {.y = 6, .x = 5};
	struct point xxx;
	struct point *p = &a;

	a = (struct point){2, 7};
	//a = {2, 7};

	xxx = a;

	//a.x = 10;
	//a.y = a.x * 10;

	printf("%d, %d\n", (*p).x, p->y);
	//printf("%d, %d\n", a.x, a.y);

	return 0;
}
