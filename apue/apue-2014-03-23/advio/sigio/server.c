#define _GNU_SOURCE

#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>

#define BUFSIZE 32

static int fa0, fa1, fb0, fb1;

void fa1_handler(int unuse)
{
	int ret;
	char buf[BUFSIZE];

	ret = read(fa1, buf, BUFSIZE);
	/* if error */
	if (ret > 0) {
		write(fb0, buf, ret);
	}
}

void fb1_handler(int unuse)
{
	int ret;
	char buf[BUFSIZE];

	ret = read(fb1, buf, BUFSIZE);
	/* if error */
	if (ret > 0) {
		write(fa0, buf, ret);
	}
}

int main(void)
{
	int ret;
	long status;

	signal(SIGIO, fa1_handler);
	signal(SIGUSR1, fb1_handler);

	fa0 = open("fa0", O_WRONLY);
	/* if error */

	fa1 = open("fa1", O_RDONLY);
        /* if error */
	fcntl(fa1, F_SETOWN, getpid());
	status = fcntl(fa1, F_GETFL);
	fcntl(fa1, F_SETFL, status | O_ASYNC);

	fb0 = open("fb0", O_WRONLY);
	/* if error */

	fb1 = open("fb1", O_RDONLY);
        /* if error */
	fcntl(fb1, F_SETOWN, getpid());
	status = fcntl(fb1, F_GETFL);
	fcntl(fb1, F_SETFL, status | O_ASYNC);
	ret = fcntl(fb1, F_SETSIG, SIGUSR1);
	if (ret == -1) {
		perror("fcntl(F_SETSIG,)");
	}

	while (1) {
		pause();
	}

	close(fb1);
	close(fb0);
	close(fa1);
	close(fa0);

	return 0;
}
