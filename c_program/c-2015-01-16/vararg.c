#include <stdio.h>

#include "myvararg.h"

int add(int a, ...)
{
	int sum = 0;
	int *p;

	for (p = &a; *p != 0; p++) {
		sum += *p;
	}

	return sum;
}

void myprintf(const char *format, ...)
{
	char *p;
	const char *f;

	p = (char *)(&format + 1);
	for (f = format; *f != '\0'; f++) {
		switch (*f) {
		case 'd':
			printf("%d ", *(int *)p);
			p += sizeof(int);
			break;
		case 'f':
			printf("%f ", *(double *)p);
                        p += sizeof(double);
			break;
		case 'c':
			printf("%c ", *(int *)p);
                        p += sizeof(int);
			break;
		case 's':
			printf("%s ", *(char **)p);
                        p += sizeof(char *);
			break;
		}
	}
	printf("\n");
}

void myprintf_lib(const char *format, ...)
{
	char *p;
	const char *f;

	myva_start(p, format);
	for (f = format; *f != '\0'; f++) {
		switch (*f) {
		case 'd':
			printf("%d ", myva_arg(p, int));
			break;
		case 'f':
			printf("%f ", myva_arg(p, double));
			break;
		case 'c':
			printf("%c ", myva_arg(p, int));
			break;
		case 's':
			printf("%s ", myva_arg(p, char *));
			break;
		}
	}
	printf("\n");
}

int main(void)
{
	int a;

	a = add(1,2,3,4,0,5,6,7,0);
	printf("a = %d\n", a);

	myprintf_lib("ddcfdsd", 3, 5, 'A', 3.14, 6, "hellodd", 7);

	return 0;
}
