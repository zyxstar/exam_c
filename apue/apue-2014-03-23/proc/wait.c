#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pid_t pid;
	int st;

	pid = fork();
	if (pid == 0) {
		printf("child: pid = %d\n", getpid());
		//sleep(10);

		exit(257);
	}
	printf("parent: pid = %d\n", getpid());
	//wait(&st);
	waitpid(-1, &st, 0);
	printf("child return %d\n", WEXITSTATUS(st));
	//sleep(30);

	exit(0);
}
