#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <errno.h>

#define BUFSIZE 5

/* $ ./a.out path */
int main(int argc, char **argv)
{
	int fd, fd_dup;
	int ret;
	char buf[BUFSIZE];
	int i;

	if (argc != 2) {
		fprintf(stderr, "argment...\n");
		return 1;
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		perror(argv[1]);
		return 1;
	}

	//fd_dup = dup(fd);
	fd_dup = open(argv[1], O_RDONLY);
	/* if error */
	printf("fd = %d, fd_dup = %d\n", fd, fd_dup);

	write(1, "\033[31m", 5);
	for (i = 0; i < 2; i++) {
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
	write(1, "\033[0m", 5);

	while (1) {
		ret = read(fd_dup, buf, BUFSIZE);
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
