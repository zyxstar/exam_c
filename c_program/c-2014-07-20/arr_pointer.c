#include <stdio.h>

int main(void)
{
	int arr[3][4];
	int (*p)[4];
	int *(q[4]);

	p = arr;

	arr[1][2];
	p[1][2];


}
