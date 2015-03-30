#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

#define BUFSIZE 128

int main(void)
{
	int fd;
	char buf[BUFSIZE];
	int ret;

	fd = open("ff", O_RDONLY);
	if (fd == -1) {
		perror("ff");
		return 1;
	}

	/* debug */
	printf("open() return\n");

	ret = read(fd, buf, BUFSIZE);
	write(1, buf, ret);

	close(fd);

	return 0;
}
