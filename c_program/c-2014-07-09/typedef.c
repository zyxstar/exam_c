#include <stdio.h>

typedef int signed32;
int aaa;

void (   *signal(  int, void (*)(int)  )    )(int);

typedef void sigfunc(int);
sigfunc *signal(int, sigfunc *);

void foo(int);
sigfunc foo;

void foo(int a)
{

}

int main(void)
{
	signed32 a;

	printf("sizeof(a) = %d\n", sizeof(a));

	return 0;
}

