#include <stdio.h>

int main(void)
{
	unsigned char c;

	while (1) {
		c = getchar();
		printf("%c", c);
	}

	return 0;
}
