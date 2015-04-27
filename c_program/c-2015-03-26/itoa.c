#include <stdio.h>

void reverse(char str[])
{
	int start, end;
	int tmp;

	start = 0;
	for (end = 0; str[end] != '\0'; end++)
		;
	end--;

	while (start < end) {
		tmp = str[start];
		str[start] = str[end];
		str[end] = tmp;

		start++; end--;
	}
}

void itoa(char buf[], int data)
{
	int i;
	int isnegtive = 0;

	if (data < 0) {
		data = -data;
		isnegtive = 1;
	}

	i = 0;
	do {
		buf[i] = data % 10 + '0';
		data /= 10;
		i++;
	} while (data != 0);
	if (isnegtive) {
		buf[i++] = '-';
	}
	buf[i] = '\0';

	reverse(buf);
}

static int itoa_rec__(char *buf, int data)
{
	char c;
	int ind;

	if (data == 0) {
		buf[0] = '\0';
		return 0;
	}

	c = data % 10 + '0';

	ind = itoa_rec__(buf, data / 10);
	buf[ind] = c;
	buf[ind + 1] = '\0';

	return ind + 1;
}

void itoa_rec(char *buf, int data)
{
	if (data == 0) {
		buf[0] = '0';
		buf[1] = '\0';
		return;
	}

	itoa_rec__(buf, data);
}

int main(void)
{
	int a = 0;
	char buf[32];

	itoa_rec(buf, a);
	printf("%s\n", buf);

	return 0;
}
