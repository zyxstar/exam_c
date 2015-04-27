#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 32

int main(void)
{
	int fa0, fa1, fb0, fb1;
	int ret;
	char buf[BUFSIZE];
	long status;

	fa0 = open("fa0", O_WRONLY);
	/* if error */

#if 0
	fa1 = open("fa1", O_RDONLY | O_NONBLOCK);
	/* if error */
#else
	fa1 = open("fa1", O_RDONLY);
        /* if error */
	status = fcntl(fa1, F_GETFL);
	status |= O_NONBLOCK;
	fcntl(fa1, F_SETFL, status);
#endif

	fb0 = open("fb0", O_WRONLY);
	/* if error */

#if 0
	fb1 = open("fb1", O_RDONLY | O_NONBLOCK);
	/* if error */
#else
	fb1 = open("fb1", O_RDONLY);
        /* if error */
	status = fcntl(fb1, F_GETFL);
	status |= O_NONBLOCK;
	fcntl(fb1, F_SETFL, status);
#endif

	while (1) {
		ret = read(fa1, buf, BUFSIZE);
		/* if error */
		if (ret == 0) {
			break;
		} else if (ret > 0) {
			write(fb0, buf, ret);
		}

		ret = read(fb1, buf, BUFSIZE);
		/* if error */
		if (ret == 0) {
			break;
		} else if (ret > 0) {
			write(fa0, buf, ret);
		}
	}

	close(fb1);
	close(fb0);
	close(fa1);
	close(fa0);

	return 0;
}
