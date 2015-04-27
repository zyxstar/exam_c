#include <stdio.h>

#define PI 3.1416

#define add(A, B) ((A) + (B))
#define mul(A, B) ((A) * (B))

//#define min(A, B) ((A) < (B) ? (A) : (B))

#define min(A, B) ({ \
			int aaa = A; \
			int bbb = B; \
			aaa < bbb ? aaa : bbb;})

#define foo(XXX) do {XXX = 5; XXX++;} while (0)

#define X86

//#if defined ARM
#ifdef ARM
xxx;
#elif defined X86
yyy;
X86;
#elif defined X64
zzz;
#endif

#if 0
int xxx(void)
{
	return 0;
}
#else
int xxx(void)
{
	return 0;
}
#endif

int main(void)
{
	double s, r;
	int a, b, c;
	float xx = 5.0;

	if (1)
		foo(a);
	else
		c = a + b;

#if 5 - 5
	b = 3, c = 5;
	a = min(b++, c++);
	printf("a = %d, b = %d, c = %d\n", a, b, c);
#endif
	r = 2.0;
	s = r * r * PI;
#undef PI
	PI;

	printf("s = %f\n", s);

	return 0;
}
