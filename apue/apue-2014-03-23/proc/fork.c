#include <unistd.h>

#include <stdio.h>

int main(void)
{
	pid_t pid;

	printf("main 1\n");

	fflush(NULL);
	pid = fork();
	printf("pid = %d\n", pid);

	printf("main 2\n");

	return 0;
}
