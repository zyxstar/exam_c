#include <unistd.h>

#include <stdio.h>

int main(void)
{
	pid_t pid;

	printf("pid = %d\n", getpid());

	printf("before fork\n");
	fflush(NULL);
	pid = fork();
	printf("after fork\n");

	if (pid != 0) {
		printf("in parent, pid = %d, fork() return %d\n", getpid(), pid);
	} else {
		printf("in child, pid = %d, fork() return %d\n", getpid(), pid);
	}

	return 0;
}
