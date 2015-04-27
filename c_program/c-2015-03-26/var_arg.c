#include <stdio.h>
#include <stdarg.h>

int add(int data, ...)
{
	int *argp;
	int sum = 0;

	for (argp = &data; *argp != 0; argp++) {
		sum += *argp;
	}
	return sum;
}

#if 0
void myprintf(const char *format, ...)
{
	char *argp;

	for (argp = (char *)(&format + 1); *format != '\0'; format++) {
		switch (*format) {
		case 'd':
			printf("%d ", *(int *)argp);
			argp += sizeof(int);
			break;
		case 'f':
			printf("%f ", *(double *)argp);
			argp += sizeof(double);
			break;
		case 'c':
			//printf("%c ", *(int *)argp);
                        //argp += sizeof(int);
			printf("%c ", *(char *)argp);
			argp += sizeof(char);
			break;
		case 's':
			printf("%s ", *(char **)argp);
                        argp += sizeof(char *);
			break;
		}
	}

	printf("\n");
}
#else
void myprintf(const char *format, ...)
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
#endif

int main(void)
{
	int a, b, c;
	char ch = 'A';
	myprintf("ddfdscd", 3, 5, 3.14, 6, "hello", ch, 7);

	a = 3, b = 6;
	c = add(1,2,3,4,5,0);

	printf("c = %d\n", c);

	return 0;
}
