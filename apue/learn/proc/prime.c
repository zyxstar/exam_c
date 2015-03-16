#include <stdio.h>

#define START 100000001
#define END   100000100

static int is_prime(int data)
{
	int i;

	for (i = 2; i < data / 2; i++) {
		if (data % i == 0) {
			return 0;
		}
	}
	return 1;
}

int main(void)
{
	int i;

	for (i = START; i <= END; i++) {
		if (is_prime(i)) {
			printf("%d ", i);
			fflush(NULL);
		}
	}

	return 0;
}
