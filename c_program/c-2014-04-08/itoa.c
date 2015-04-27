#include <stdio.h>

void itoa(char str[], int data)
{
	int i;
	int is_neg = 0;

	if (data < 0) {
		data = -data;
		is_neg = 1;
	}

	i = 0;
	do {
		str[i] = data % 10 + '0';
		data /= 10;
		i++;
	} while (data > 0);
	if (is_neg) {
		str[i++] = '-';
	}
	str[i] = '\0';
}

int main(void)
{
	char str[64];

	itoa(str, 12345);
	printf("%s\n", str);

	return 0;
}
