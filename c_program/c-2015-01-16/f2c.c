#include <stdio.h>

#define START 0
#define END   300
#define STEP  20

int main(void)
{
	int f, c;

	for (f = START; f <= END; f = f + STEP) {
		c = 5 * (f - 32) / 9;
		printf("%d\t\t%d\n", f, c);
	}

/*
	f = 0;
	while (f <= 300) {
		c = 5 * (f - 32) / 9;
		printf("%d\t%d\n", f, c);
		f = f + 20;
	}

	f = 0;
xxx:
	c = 5 * (f - 32) / 9;
	printf("%d\t%d\n", f, c);
	f = f + 20;
	if (f <= 300) {
		goto xxx;
	}
*/

	return 0;
}
