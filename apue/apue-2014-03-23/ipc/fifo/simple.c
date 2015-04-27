#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 128

int main(void)
{
	pid_t pid;
	int fd;
	char buf[BUFSIZE];
	int ret;

	mkfifo("ff", 0666);
	/* if error */

	pid = fork();
	/* if error */

	if (pid == 0) {
		fd = open("ff", O_WRONLY);
		/* if error */

		write(fd, "hello fifo\n", 11);

		close(fd);
		exit(0);
	}

	fd = open("ff", O_RDONLY);
	/* if error */

	ret = read(fd, buf, BUFSIZE);
	write(1, buf, ret);

	close(fd);
	return 0;
}
