#include <stdio.h>
#include <stdarg.h>

int add(int a, ...)
{
	int sum = 0;
	int *p;

	for (p = &a; *p != 0; p++) {
		sum += *p;
	}

	return sum;
}

#if 0
void myprintf(const char *format, ...)
{
	char *p;

	p = (char *)(&format + 1);
	while (*format != '\0') {
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
			printf("%c ", *(char *)p);
			p += sizeof(int);
			break;
		case 's':
			printf("%s ", *(char **)p);
			p += sizeof(char *);
			break;
		}
		format++;
	}
	printf("\n");
}
#else
void myprintf(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);

	while (*format != '\0') {
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
		format++;
	}
	printf("\n");

	va_end(ap);
}
#endif

int main(void)
{
	int a;

	//a = add(11, 22, 33, 44, 55, 66, 0);
	//printf("a = %d\n", a);

	myprintf("cdcfdsdd", 'A', 11, 'X', 3.14, 22, "hello", 33, 44);

	return 0;
}
