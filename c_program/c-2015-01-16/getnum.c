#include <stdio.h>

int main(void)
{
	char arr[32];
	int i;
	int num;

	for (i = 0; ; i = i + 1) {
		arr[i] = getchar();
		if (arr[i] == '\n') {
			arr[i] = '\0';
			break;
		}
	}

/*
	num = 0;
	for (i = 0; arr[i] != '\0'; i = i + 1) {
		num = num * 10 + arr[i] - '0';
	}
*/
	num = atoi(arr);
	printf("num = %d\n", num);

	return 0;
}
