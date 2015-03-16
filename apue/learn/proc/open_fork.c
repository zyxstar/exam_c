#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

#define BUFSIZE 32

int main(void)
{
	int fd;
	pid_t pid;
	char buf[BUFSIZE];
	int ret;

	fd = open("fork.c", O_RDONLY);
	if (fd == -1) {
		perror("open(fork.c)");
		return 1;
	}

	pid = fork();
	/* if error */
	if (pid == 0) {
		ret = read(fd, buf, BUFSIZE);
		write(1, "\033[31m", 5);
		write(1, buf, ret);
		write(1, "\033[0m", 4);

		close(fd);
		return 0;
	}

	wait(NULL);

	while (1) {
		ret = read(fd, buf, BUFSIZE);
		if (ret == 0) {
			break;
		}
		write(1, buf, ret);
	}

	close(fd);

	return 0;
}
