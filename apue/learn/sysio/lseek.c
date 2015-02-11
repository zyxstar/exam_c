#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

#define BUFSIZE  32

/* ./a.out path */
int main(int argc, char **argv)
{
	int fd;
	char buf[BUFSIZE];
	int ret;

	if (argc != 2) {
		printf("argment...\n");
		return 1;
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		printf("open %s failed.\n", argv[1]);
		return 1;
	}

	lseek(fd, 9, SEEK_SET);

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
