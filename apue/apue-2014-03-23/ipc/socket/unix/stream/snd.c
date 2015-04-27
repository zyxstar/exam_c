#define UNIX_PATH_MAX    108

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUFSIZE 256

int main(void)
{
	int sd;
	struct sockaddr_un hisend;
	int ret;
	char buf[BUFSIZE];

	sd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sd == -1) {
		perror("socket()");
		goto socket_err;
	}

	hisend.sun_family = AF_UNIX;
	snprintf(hisend.sun_path, UNIX_PATH_MAX, "rcv_sock");
	ret = connect(sd, (struct sockaddr *)&hisend, sizeof(hisend));
	if (ret == -1) {
		perror("connect()");
		goto connect_err;
	}

	while (1) {
		ret = read(0, buf, BUFSIZE);
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
