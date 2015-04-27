#include <unistd.h>

#include <stdio.h>

#define START 100000000
#define END   100000100

int is_prime(int data)
{
	int i;
	int half = data / 2;

	for (i = 2; i < half; i++) {
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
		}
	}
	printf("\n");

	return 0;
}
