#include <stdio.h>

void xxx(void)
{
	printf("xxx\n");
}

void bar(void)
{
	char buf[4];
	int i;

	for (i = 0; i < 24; i++) {
		printf("%x ", (unsigned char)buf[i]);
	}
	printf("\n");

	gets(buf);
}

void foo(void)
{
	printf("in foo() 1\n");
	bar();
	printf("in foo() 2\n");
}

int main(void)
{
	printf("in main() 1\n");
	foo();
	printf("in main() 2\n");

	return 0;
}
