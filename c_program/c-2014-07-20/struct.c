#include <stdio.h>

struct coop {
	int x;
	int y;
};

struct circle {
	struct coop cent;
	//int x, y;
	int r;
};

int main(void)
{
	struct circle xx;

	xx.cent.x;

	//struct coop a = {123};
	struct coop a = {.y = 66};
	struct coop *p;
	int arr[5000] = {[2000] = 33, [3000] = 44};

	p = &a;

	//a.x = 123;
	//a.y = a.x * 2;

	printf("x: %d, y: %d\n", a.x, a.y);
	printf("x: %d, y: %d\n", (*p).x, (*p).y);
	printf("x: %d, y: %d\n", p->x, p->y);
	printf("[1000] = %d, [2000] = %d, [3000] = %d\n", arr[1000], arr[2000], arr[3000]);

	return 0;
}
