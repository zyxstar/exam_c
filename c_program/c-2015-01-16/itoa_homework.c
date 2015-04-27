#include <stdio.h>

void itoa(char buf[], int data)
{
	int i;
	int is_neg = 0;

	if (data < 0) {
		is_neg = 1;
	}

	i = 0;
	do {
		if (is_neg) {
			buf[i] = -(data % 10) + '0';
		} else {
			buf[i] = data % 10 + '0';
		}

		data /= 10;
		i++;
	} while (data != 0);

	if (is_neg) {
		buf[i++] = '-';
	}

	buf[i] = '\0';
}

int main(void)
{
	char str[32];
	int a = -10000;

	itoa(str, a);

	printf("%s\n", str);

	return 0;
}
