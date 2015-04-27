#include <stdio.h>

#if 0
int op(int a, int b)
{
	return a + b;
}
#elif 6
int op(int a, int b)
{
        return a * b;
}
#else
int op(int a, int b)
{
        return a / b;
}
#endif

//#define DEBUG

#if defined DEBUG
uuuuuuuuuuuuuuuuuuuuu;
#endif

void foo(void)
{
#if defined X86
	xxxxxxxxx;
#elif defined ARM
	yyyyyyyyyy;
#endif
}

//DEBUG;

int main(void)
{
	int a;

	a = op(3, 4);
	printf("a = %d\n", a);

	return 0;
}
