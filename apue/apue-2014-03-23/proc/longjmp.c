#include <setjmp.h>

#include <stdio.h>

jmp_buf point_1;

void foo(void)
{
	printf("foo 1\n");
	longjmp(point_1, 5);
	printf("foo 2\n");
}

int main(void)
{
	int ret;

	printf("main 1\n");
	ret = setjmp(point_1);
	printf("setjmp() return %d\n", ret);
	if (ret == 0) {
		printf("main 2\n");
		foo();
	}

	printf("main 3\n");

	return 0;
}
