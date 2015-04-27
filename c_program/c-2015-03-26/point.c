#include <stdio.h>

int main(void)
{
	int a = 12345;
	int *p = &a;

	void *qq = NULL;

	printf("a = %d\n", a);
	printf("*p = %d\n", *p);

	*p = 234;
	printf("a = %d\n", a);
        printf("*p = %d\n", *p);

	return 0;
}
