#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

#define BUFSIZE   16

int main(void)
{
	int fd;
	int ret;
	char buf[BUFSIZE];

	fd = open("ff", O_WRONLY);
	if (fd == -1) {
		perror("ff");
		return 1;
	}
	write(1, "open() return\n", 14);

	while (1) {
		ret = read(0, buf, BUFSIZE);
		/* if error */
		if (ret == 0) {
			break;
		}

		write(fd, buf, ret);
	}

	close(fd);
	return 0;
}
