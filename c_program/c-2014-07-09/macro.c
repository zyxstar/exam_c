#include <stdio.h>

#if 0
int add(int a, int b)
{
	int c;
	c = a + b;		/*  */
	return c;
}
#endif

#define add(A, B) ((A) + (B))
#define mul(A, B) ((A) * (B))

#if 5
#define min(A, B) ((A) < (B) ? (A) : (B))
#else
#define min(A, B) ((A) < (c) ? (A) : (B))
#endif

#define min(X, Y) ({ \
	int xxx = (X); \
	int yyy = (Y); \
	xxx < yyy ? xxx : yyy; \
		})

#define xxx(A) do {aaa; yyy;} while (0)

int main(void)
{
	if ()
		xxx();
	else
		yyy();

	int xxx, yyy, c;
	xxx = 3, yyy = 7;
	c = min(xxx++, yyy++);
#undef min
	c = min(xxx++, yyy++);

	printf("xxx = %d, yyy = %d, c = %d\n", xxx, yyy, c);

	return 0;
}
