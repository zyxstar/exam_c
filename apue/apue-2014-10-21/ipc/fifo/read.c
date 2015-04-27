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

	fd = open("ff", O_RDONLY);
	if (fd == -1) {
		perror("ff");
		return 1;
	}
	write(1, "open() return\n", 14);

	while (1) {
		ret = read(fd, buf, BUFSIZE);
		/* if error */
		if (ret == 0) {
			break;
		}

		write(1, "\033[31m", 5);
		write(1, buf, ret);
		write(1, "\033[0m", 4);
	}

	close(fd);
	return 0;
}
