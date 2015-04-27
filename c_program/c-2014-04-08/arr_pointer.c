#include <stdio.h>

int main(void)
{
	int arr[6] = {111,222,333,444,};
	int (*p)[6];
	int i;

	p = &arr;
	for (i = 0; i < 6; i++) {
		printf("%d\n", (*p)[i]);
	}

	return 0;
}
