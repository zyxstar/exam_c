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
	struct sockaddr_un myend, hisend;
	socklen_t hislen;
	int ret;
	char buf[BUFSIZE];

	sd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if (sd == -1) {
		perror("socket()");
		goto socket_err;
	}

	myend.sun_family = AF_UNIX;
	snprintf(myend.sun_path, UNIX_PATH_MAX, "rcv_sock");
	unlink(myend.sun_path);
	ret = bind(sd, (struct sockaddr *)&myend, sizeof(myend));
	if (ret == -1) {
		perror("bind()");
		goto bind_err;
	}

	hislen = sizeof(hisend);
	while (1) {
		ret = recvfrom(sd, buf, BUFSIZE, 0, (struct sockaddr *)&hisend, &hislen);
		if (ret == 0) {
			break;
		}
		write(1, buf, ret);
		sendto(sd, "qnmlgb", 6, 0, (struct sockaddr *)&hisend, hislen);
	}

	close(sd);

	return 0;



bind_err:
	close(sd);
socket_err:
	return 1;
}
