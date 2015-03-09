#include <stdio.h>

#define STRSIZE  32

/* ./a.out */
/* int double string int */
int main(void)
{
	int a, b;
	double d;
	char str[STRSIZE];
	char buf[STRSIZE];

	//scanf("%d %lf %s %d", &a, &d, str, &b);
	fgets(buf, STRSIZE, stdin);
	sscanf(buf, "%d %lf %s %d", &a, &d, str, &b);

	printf("%d, %d, %f, %s\n", a, b, d, str);

	return 0;
}
