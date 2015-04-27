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
	int sd;
	struct sockaddr_un myend, hisend;
	socklen_t hislen;
	int ret;
	char buf[BUFSIZE];

	sd = socket(AF_LOCAL, SOCK_DGRAM, 0);
	if (sd == -1) {
		perror("socket()");
		goto socket_err;
	}

	myend.sun_family = AF_UNIX;
	while (1) {
		snprintf(myend.sun_path, UNIX_PATH_MAX, "./socket_XXXXXX");
		mktemp(myend.sun_path);
		ret = bind(sd, (struct sockaddr *)&myend, sizeof(myend));
		if (ret == 0) {
			break;
		}
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

		ret = read(sd, buf, BUFSIZE);
		write(1, buf, ret);
	}


	unlink(myend.sun_path);
	close(sd);
	return 0;


connect_err:
	unlink(myend.sun_path);
	close(sd);
socket_err:
	return 1;
}
