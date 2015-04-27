#include <stdio.h>

int main(void)
{
	int a = 4;
	int *p = &a;

	//p = &a;
	printf("%d\n", *p);
	*p = 6;
	printf("%d\n", a);

	return 0;
}
