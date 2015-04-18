#define UNIX_PATH_MAX    108

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 32

int main(void)
{
	int sd;
	struct sockaddr_un hisend;
	int ret;
	char buf[BUFSIZE];

	sd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sd == -1) {
		perror("socket()");
		return 1;
	}

	hisend.sun_family = AF_UNIX;
	snprintf(hisend.sun_path, UNIX_PATH_MAX, "sock_recv");
	ret = connect(sd, (struct sockaddr *)&hisend, sizeof(hisend));
	if (ret == -1) {
		perror("connect()");
		return 1;
	}

	while (1) {
		ret = read(0, buf, BUFSIZE);
		/* if error */
		if (ret == 0) {
			break;
		}

		write(sd, buf, ret);

		ret = read(sd, buf, BUFSIZE);
		write(1, buf, ret);
	}

	close(sd);

	return 0;
}
