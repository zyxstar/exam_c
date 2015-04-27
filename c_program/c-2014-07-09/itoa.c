#include <stdio.h>

#if 1
void itoa(int data, char str[])
{
	int i;
	int is_neg = 0;

	if (data < 0) {
		is_neg = 1;
	}

	i = 0;
	do {
		if (is_neg) {
			str[i] = -(data % 10) + '0';
		} else {
			str[i] = data % 10 + '0';
		}
		data /= 10;
		i++;
	} while (data != 0);

	if (is_neg) {
		str[i++] = '-';
	}

	str[i] = '\0';
}
#else
int itoa__(int data, char str[])
{
	char c;
	int ind;

	if (data == 0) {
		return 0;
	}

	c = data % 10 + '0';
	ind = itoa__(data / 10, str);
	str[ind++] = c;

	return ind;
}

void itoa(int data, char str[])
{
	int ind;

	if (data == 0) {
		str[0] = '0';
		str[1] = '\0';
		return;
	}

	ind = itoa__(data, str);
	str[ind] = '\0';
}
#endif

int main(void)
{
	char str[32];

	itoa(-32167, str);
	printf("%s\n", str);

	return 0;
}
