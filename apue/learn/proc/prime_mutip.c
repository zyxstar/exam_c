#include <unistd.h>

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
	pid_t pid;

	pid = fork();
	/* if error */
	if (pid == 0) {
		for (i = (START + END) / 2; i <= END; i++) {
			if (is_prime(i)) {
				printf("%d ", i);
				fflush(NULL);
			}
		}

		return 0;
	}

	for (i = START; i < (START + END) / 2; i++) {
		if (is_prime(i)) {
			printf("%d ", i);
			fflush(NULL);
		}
	}

	wait(NULL);

	return 0;
}
