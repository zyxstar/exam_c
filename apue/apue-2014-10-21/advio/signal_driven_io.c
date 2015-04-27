#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>

#include <stdio.h>

#define BUFSIZE   128

static int fd;

static void handler(int unuse)
{
	char buf[BUFSIZE];
	int ret;

	ret = read(fd, buf, BUFSIZE);
	write(1, buf, ret);
}

int main(void)
{
	long status;

	signal(SIGIO, handler);

	fd = open("ff", O_RDONLY);
	if (fd == -1) {
		perror("open(ff)");
		return 1;
	}

	status = fcntl(fd, F_GETFL);
	status |= O_ASYNC;
	fcntl(fd, F_SETFL, status);
	/* if error */

	fcntl(fd, F_SETOWN, getpid());
	/* if error */

	while (1) {
		pause();
	}

	close(fd);

	return 0;
}
