#define UNIX_PATH_MAX    108

#include <sys/types.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define BUFSIZE 32

int main(void)
{
	int sd, newsd;
	struct sockaddr_un myend, hisend;
	socklen_t hislen;
	char buf[BUFSIZE];
	int ret;

	sd = socket(AF_LOCAL, SOCK_STREAM, 0);
	if (sd == -1) {
		perror("socket()");
		goto socket_err;
	}

	hisend.sun_family = AF_UNIX;
	snprintf(hisend.sun_path, UNIX_PATH_MAX, "./socket_r");
	ret = connect(sd, (struct sockaddr *)&hisend, sizeof(hisend));
	if (ret == -1) {
		perror("connect()");
		goto connect_err;
	}

	while (1) {
		ret = read(0, buf, BUFSIZE);
		/* if error */
		if (ret == 0) {
			break;
		}

		write(sd, buf, ret);
	}

	close(sd);
	return 0;



connect_err:
	close(sd);
socket_err:
	return 1;
}
