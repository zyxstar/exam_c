#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <errno.h>

#define BUFSIZE    256

int main(void)
{
	int fdr, fdw;
	int ret;
	char buf[BUFSIZE];
	long flags;

	fdr = open("ff1", O_RDONLY | O_NONBLOCK);
	if (fdr == -1) {
		perror("ff1");
		goto open_fdr_err;
	}

	fdw = open("ff2", O_WRONLY);
	if (fdw == -1) {
		perror("ff2");
		goto open_fdw_err;
	}

	flags = fcntl(0, F_GETFL);
	flags |= O_NONBLOCK;
	fcntl(0, F_SETFL, flags);
	/* if error */

	while (1) {
		ret = read(0, buf, BUFSIZE);
		if (!(ret == -1 && errno == EAGAIN)) {
			if (ret == -1) {
				/* error */
			}
			if (ret == 0) {
				break;
			}

			write(fdw, buf, ret);
			/* if error */
		}

		ret = read(fdr, buf, BUFSIZE);
		if (!(ret == -1 && errno == EAGAIN)) {
			if (ret == -1) {
				/* error */
			}
			if (ret == 0) {
				break;
			}

			write(1, "\033[31m", 5);
			write(1, buf, ret);
			write(1, "\033[0m", 4);
			/* if error */
		}
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
