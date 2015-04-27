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
	int mid;
	pid_t pid;

	pid = fork();
	if (pid == -1) {
		perror("fork()");
		return 1;
	}

	mid = (START + END) / 2;

	if (pid == 0) {
		for (i = START; i < mid; i++) {
			if (is_prime(i)) {
				printf("%d ", i);
			}
		}
		printf("\n");
		return 0;
	}

	for (i = mid; i <= END; i++) {
		if (is_prime(i)) {
			printf("%d ", i);
		}
	}
	printf("\n");
	wait(NULL);
	return 0;
}
