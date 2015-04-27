#include <sys/time.h>
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
	fd_set rset;

	fdr = open("ff1", O_RDONLY);
	if (fdr == -1) {
		perror("ff1");
		goto open_fdr_err;
	}

	fdw = open("ff2", O_WRONLY);
	if (fdw == -1) {
		perror("ff2");
		goto open_fdw_err;
	}

	while (1) {
		FD_ZERO(&rset);
		FD_SET(0, &rset);
		FD_SET(fdr, &rset);
		ret = select(fdr + 1, &rset, NULL, NULL, NULL);
		if (ret == -1) {
			if (errno == EINTR) {
				continue;
			}
			perror("select()");
			break;
		}

		if (FD_ISSET(0, &rset)) {
			ret = read(0, buf, BUFSIZE);
			/* if error */
			if (ret == 0) {
				break;
			}

			write(fdw, buf, ret);
			/* if error */
		}

		if (FD_ISSET(fdr, &rset)) {
			ret = read(fdr, buf, BUFSIZE);
			/* if error */
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
