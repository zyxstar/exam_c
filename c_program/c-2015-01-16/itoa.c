#include <stdio.h>

/*
void itoa(char buf[], int data)
{
	int i;
	int is_neg = 0;

	if (data < 0) {
		is_neg = 1;
		data = -data;
	}

	i = 0;
	do {
		buf[i] = data % 10 + '0';
		data /= 10;
		i++;
	} while (data != 0);

	if (is_neg) {
		buf[i++] = '-';
	}

	buf[i] = '\0';
}
*/
static int itoa_(char buf[], int data)
{
	char c;
	int ind;

	if (data == 0) {
		return 0;
	}

	c = data % 10 + '0';
	ind = itoa_(buf, data / 10);
	buf[ind] = c;

	return ind + 1;
}

void itoa(char buf[], int data)
{
	int ind;

	if (data == 0) {
		buf[0] = '0';
		buf[1] = '\0';
	} else {
		ind = itoa_(buf, data);
		buf[ind] = '\0';
	}
}

int main(void)
{
	char str[32];
	int a = 32167;

	//itoa(str, a);
	itoa(str, a);

	printf("%s\n", str);

	return 0;
}
