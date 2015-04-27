#include <stdio.h>

#include <stdarg.h>

void myprintf_lib(const char *format, ...)
{
	va_list p;
	const char *f;

	va_start(p, format);
	for (f = format; *f != '\0'; f++) {
		switch (*f) {
		case 'd':
			printf("%d ", va_arg(p, int));
			break;
		case 'f':
			printf("%f ", va_arg(p, double));
			break;
		case 'c':
			printf("%c ", va_arg(p, int));
			break;
		case 's':
			printf("%s ", va_arg(p, char *));
			break;
		}
	}
	printf("\n");

	va_end(p);
}

int add(int first, ...)
{
	va_list ap;
	int sum;
	int val;

	va_start(ap, first);

	sum = first;
	while (1) {
		val = va_arg(ap, int);
		if (val == 0) {
			break;
		}

		sum += val;
	}

	va_end(ap);

	return sum;
}

int add_num(int num, ...)
{
	va_list ap;
	int sum;
	int val;
	int i;

	va_start(ap, num);

	sum = 0;
	for (i = 0; i < num; i++) {
		val = va_arg(ap, int);
		sum += val;
	}

	va_end(ap);

	return sum;
}

int main(void)
{
	int a;

	a = add_num(7,1,2,3,4,5,0,6);
	printf("a = %d\n", a);

	myprintf_lib("ddcfdsd", 3, 5, 'A', 3.14, 6, "hellodd", 7);

	return 0;
}
