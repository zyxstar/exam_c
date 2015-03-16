#include <setjmp.h>

#include <stdio.h>

static jmp_buf env;

void bar(void)
{
	printf("%s 1\n", __func__);
	longjmp(env, 123);
        printf("%s 2\n", __func__);
}

void foo(void)
{
	printf("%s 1\n", __func__);
	bar();
	printf("%s 2\n", __func__);
}

int main(void)
{
	int val;

	printf("%s 1\n", __func__);
	val = setjmp(env);
	if (val == 0) {
		printf("%s 2\n", __func__);
		foo();
	}
	printf("%s 3, val = %d\n", __func__, val);

	return 0;
}
