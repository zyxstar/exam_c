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

	myend.sun_family = AF_UNIX;
	snprintf(myend.sun_path, UNIX_PATH_MAX, "./socket_r");
	unlink(myend.sun_path);
	ret = bind(sd, (struct sockaddr *)&myend, sizeof(myend));
	if (ret == -1) {
		perror("bind()");
		goto bind_err;
	}

	listen(sd, 20);

	hislen = sizeof(hisend);
	newsd = accept(sd, (struct sockaddr *)&hisend, &hislen);
	/* if error */

	while (1) {
		ret = read(newsd, buf, BUFSIZE);
		/* if error */
		if (ret == 0) {
			break;
		}

		write(1, buf, ret);
	}

	close(newsd);
	close(sd);
	return 0;



bind_err:
	close(sd);
socket_err:
	return 1;
}
