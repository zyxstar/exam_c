#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <errno.h>

#define BUFSIZE 32

/* $ ./a.out path */
int main(int argc, char **argv)
{
	int fd;
	int ret;
	char buf[BUFSIZE];

	if (argc != 2) {
		fprintf(stderr, "argment...\n");
		return 1;
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		perror(argv[1]);
		return 1;
	}

	while (1) {
		ret = read(fd, buf, BUFSIZE);
		if (ret == 0) {
			break;
		}
		if (ret == -1) {
			if (errno == EINTR) {
				continue;
			}
			perror("read()");
			break;
		}

		write(1, buf, ret);
	}

	close(fd);

	return 0;
}
