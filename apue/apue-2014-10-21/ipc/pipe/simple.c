#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE  32

int main(void)
{
	pid_t pid;
	int fd[2];
	char buf[BUFSIZE];
	int ret;

	pipe(fd);

	pid = fork();
	/* if error */
	if (pid == 0) {
		close(fd[0]);
		write(fd[1], "hello pipe\n", 11);
		close(fd[1]);

		exit(0);
	}

	close(fd[1]);
	ret = read(fd[0], buf, BUFSIZE);
	close(fd[0]);
	write(1, buf, ret);

	return 0;
}
