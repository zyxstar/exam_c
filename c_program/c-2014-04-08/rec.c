#include <stdio.h>

int getmax(int m, int n)
{
	return m > n ? m : n;
}

int getmin(int m, int n)
{
	return m < n ? m : n;
}

int factor(int n)
{
	if (n == 1) {
		return 1;
	}
	return n * factor(n - 1);
}

int fb(int n)
{
	if (n == 1 || n == 2) {
		return 1;
	}
	return fb(n - 1) + fb(n - 2);
}

int divisor(int m, int n)
{
	int max, min;

	max = getmax(m, n);
	min = getmin(m, n);

	if (max % min == 0) {
		return min;
	}
	return divisor(min, max % min);
}

int itoa(char buf[], int data)
{
	int ind;

	if (data == 0) {
		buf[0] = '\0';
		return 0;
	}

	ind = itoa(buf, data / 10);
	buf[ind++] = data % 10 + '0';
	buf[ind] = '\0';
	return ind;
}

int main(void)
{
	int ret;
	char buf[32];

	//ret = divisor(1024, 128 * 94);
	//ret = fb(9);
	//printf("%d\n", ret);
	itoa(buf, 32167);
	printf("%s\n", buf);

	return 0;
}
