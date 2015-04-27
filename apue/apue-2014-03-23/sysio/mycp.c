#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <errno.h>

#define BUFSIZE 32

/* $ ./a.out src dest */
int main(int argc, char **argv)
{
	int fdr, fdw;
	int ret, retr, retw;
	char buf[BUFSIZE];

	if (argc != 3) {
		fprintf(stderr, "argment...\n");
		return 1;
	}

	fdr = open(argv[1], O_RDONLY);
	if (fdr == -1) {
		perror(argv[1]);
		goto open_fdr_err;
	}

	fdw = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdw == -1) {
		perror(argv[2]);
		goto open_fdw_err;
	}

	while (1) {
		retr = read(fdr, buf, BUFSIZE);
		if (retr == 0) {
			break;
		}
		if (retr == -1) {
			if (errno == EINTR) {
				continue;
			}
			perror("read()");
			goto read_err;
		}

		retw = 0;
		while (retw < retr) {
			ret = write(fdw, buf + retw, retr - retw);
			if (ret == -1) {
				if (errno == EINTR) {
					continue;
				}
				perror("write()");
				goto write_err;
			}
			retw += ret;
		}
	}

	close(fdw);
	close(fdr);

	return 0;


write_err:
read_err:
	close(fdw);
open_fdw_err:
	close(fdr);
open_fdr_err:
	return 1;
}
