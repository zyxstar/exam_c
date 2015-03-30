#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

#define BUFSIZE 128

int main(void)
{
	int fdr, fdw;
	int ret;
	char buf[BUFSIZE];
	long flags;

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

	flags = fcntl(0, F_GETFL);
	flags |= O_NONBLOCK;
	fcntl(0, F_SETFL, flags);

	flags = fcntl(fdr, F_GETFL);
	flags |= O_NONBLOCK;
	fcntl(fdr, F_SETFL, flags);

	while (1) {
		ret = read(fdr, buf, BUFSIZE);
		/* if error */
		if (ret == 0) {
			break;
		}
		if (ret > 0) {
			write(1, "\033[31m", 5);
			write(1, buf, ret);
			write(1, "\033[0m", 4);
		}

		ret = read(0, buf, BUFSIZE);
		/* if error */
		if (ret == 0) {
			break;
		}
		if (ret > 0) {
			write(fdw, buf, ret);
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
