#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 32

static int max(int a, int b)
{
	return a > b ? a : b;
}

int main(void)
{
	int fa0, fa1, fb0, fb1;
	int ret;
	char buf[BUFSIZE];
	long status;
	fd_set set;
	int nfds;

	fa0 = open("fa0", O_WRONLY);
	/* if error */

	fa1 = open("fa1", O_RDONLY);
        /* if error */

	fb0 = open("fb0", O_WRONLY);
	/* if error */

	fb1 = open("fb1", O_RDONLY);
        /* if error */

	while (1) {
		FD_ZERO(&set);
		FD_SET(fa1, &set);
		FD_SET(fb1, &set);
		nfds = max(fa1, fb1) + 1;
		select(nfds, &set, NULL, NULL, NULL);

		if (FD_ISSET(fa1, &set)) {
			ret = read(fa1, buf, BUFSIZE);
			/* if error */
			if (ret == 0) {
				break;
			} else if (ret > 0) {
				write(fb0, buf, ret);
			}
		}

		if (FD_ISSET(fb1, &set)) {
			ret = read(fb1, buf, BUFSIZE);
			/* if error */
			if (ret == 0) {
				break;
			} else if (ret > 0) {
				write(fa0, buf, ret);
			}
		}
	}

	close(fb1);
	close(fb0);
	close(fa1);
	close(fa0);

	return 0;
}
