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

	fdw = open("f1", O_WRONLY);
	if (fdw == -1) {
		perror("f1");
                goto open_fdw_err;
	}

	fdr = open("f2", O_RDONLY);
	if (fdr == -1) {
		perror("f2");
		goto open_fdr_err;
	}

	while (1) {
		ret = read(0, buf, BUFSIZE);
		/* if error */
		if (ret == 0) {
			break;
		}
		write(fdw, buf, ret);

		ret = read(fdr, buf, BUFSIZE);
		/* if error */
		if (ret == 0) {
			break;
		}
		write(1, "\033[31m", 5);
		write(1, buf, ret);
		write(1, "\033[0m", 4);
	}

	close(fdr);
	close(fdw);

	return 0;


	close(fdr);
open_fdr_err:
	close(fdw);
open_fdw_err:
	return 1;
}
