#include <stdio.h>
#include <stdarg.h>

#include "myarg.h"

int add(int a, ...)
{
	int *p = &a;
	int total = 0;

	while (*p != 0) {
		total += *p;
		p++;
	}

	return total;
}

#if 1
void my_printf(const char *format, ...)
{
	myva_list ap;

	myva_start(ap, format);
	for (; *format != '\0'; format++) {
		switch (*format) {
		case 'd':
			printf("%d ", myva_arg(ap, int));
			break;
		case 'f':
			printf("%f ", myva_arg(ap, double));
			break;
		case 'c':
			printf("%c ", myva_arg(ap, char));
			break;
		case 's':
			printf("%s ", myva_arg(ap, char *));
			break;
		}
	}
	myva_end(ap);

	printf("\n");
}
#elif 0
void my_printf(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	for (; *format != '\0'; format++) {
		switch (*format) {
		case 'd':
			printf("%d ", va_arg(ap, int));
			break;
		case 'f':
			printf("%f ", va_arg(ap, double));
			break;
		case 'c':
			printf("%c ", va_arg(ap, int));
			break;
		case 's':
			printf("%s ", va_arg(ap, char *));
			break;
		}
	}
	va_end(ap);

	printf("\n");
}
#else
void my_printf(const char *format, ...)
{
	char *p;

	p = (char *)&format + sizeof(char *);
	for (; *format != '\0'; format++) {
		switch (*format) {
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
#endif

int main(void)
{
	int a;
	char c = 'A';

	a = add(1,2,3,4,5,6,0);
	printf("a = %d\n", a);

	my_printf("ddscfd", 3, 4, "hello", c, 3.14, 9);

	return 0;
}
