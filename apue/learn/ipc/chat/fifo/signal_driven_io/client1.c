#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define BUFSIZE 128

static int fdr;
static int fdw;

static void handler(int unuse)
{
	int ret;
	char buf[BUFSIZE];

	ret = read(fdr, buf, BUFSIZE);
	if (ret == -1) {
		return;
	}
	if (ret == 0) {
		exit(0);
	}
	write(1, "\033[31m", 5);
	write(1, buf, ret);
	write(1, "\033[0m", 4);
}

int main(void)
{
	int ret;
	char buf[BUFSIZE];
	long flags;

	signal(SIGIO, handler);

	fdr = open("f1", O_RDONLY);
	if (fdr == -1) {
		perror("f1");
		goto open_fdr_err;
	}

	fdw = open("f2", O_WRONLY);
	if (fdw == -1) {
		perror("f2");
                goto open_fdw_err;
	}

	flags = fcntl(fdr, F_GETFL);
	flags |= O_ASYNC;
	fcntl(fdr, F_SETFL, flags);

	fcntl(fdr, F_SETOWN, getpid());

	while (1) {
		ret = read(0, buf, BUFSIZE);
		if (ret == -1) {
			if (errno == EINTR) {
				continue;
			}
			perror("read()");
			break;
		}
		if (ret == 0) {
			break;
		}
		write(fdw, buf, ret);
	}

	close(fdw);
	close(fdr);

	return 0;


	close(fdw);
open_fdw_err:
	close(fdr);
open_fdr_err:
	return 1;
}
