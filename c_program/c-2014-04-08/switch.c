#include <stdio.h>

int main(void)
{
	int a = 2;

	switch (a) {
	case 0:
		printf("0\n");
		break;
	case 1:
		printf("1\n");
		//break;
	case 2:
		printf("2\n");
		break;
	case 3:
		printf("3\n");
		break;
	default:
		printf("else\n");
		break;
	}
/*
	if (a == 0) {
		printf("0\n");
	} else if (a == 1) {
		printf("1\n");
	} else if (a == 2) {
		printf("2\n");
	} else if (a == 3) {
		printf("3\n");
	} else {
		printf("else\n");
	}
*/
	return 0;
}
