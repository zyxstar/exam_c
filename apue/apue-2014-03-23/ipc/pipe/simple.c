#include <unistd.h>

#include <stdio.h>

#define BUFSIZE 128

int main(void)
{
	pid_t pid;
	int fd[2];
	int ret;
	char buf[BUFSIZE];

	pipe(fd);

	pid = fork();
	/* if error */

	if (pid == 0) {
		close(fd[0]);
		write(fd[1], "hello pipe\n", 11);

		close(fd[1]);
		return 0;
	}

	close(fd[1]);
	ret = read(fd[0], buf, BUFSIZE);
	write(1, buf, ret);
	close(fd[0]);

	return 0;
}
