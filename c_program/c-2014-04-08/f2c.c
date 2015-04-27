#include <stdio.h>

#define START   0
#define END     300
#define STEP    20

int main(void)
{
	int c, f;

	f = START;
	while (f <= END) {
		c = 5 * (f - 32) / 9;
		printf("%d     %d\n", f, c);
		//f = f + STEP;
		f += STEP;
	}

	return 0;
}
