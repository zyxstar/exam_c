#include <stdio.h>

int main(void)
{
	//char arr[8] = "123";
	//char arr[] = {'1', '2', '3', '4', '5'};
	char arr[8] = {
		[2] = 3,
		[3] = 6,
	};
	char *p = "123";

	//arr[2] = 6;
	//arr[0] = arr[2] * 3;

	printf("arr[0] = %d\n", arr[0]);
	printf("arr[1] = %d\n", arr[1]);
	printf("arr[2] = %d\n", arr[2]);
	printf("arr[3] = %d\n", arr[3]);
	printf("arr[4] = %d\n", arr[4]);
	printf("arr[5] = %d\n", arr[5]);

	return 0;
}
