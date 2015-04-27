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
	int sd, newsd;
	struct sockaddr_un myend;
	int ret;
	char buf[BUFSIZE];

	sd = socket(AF_UNIX, SOCK_STREAM, 0);
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

	listen(sd, 20);

	newsd = accept(sd, NULL, NULL);
	if (newsd == -1) {
		perror("accept()");
		goto accept_err;
	}

	while (1) {
		ret = read(newsd, buf, BUFSIZE);
		if (ret == 0) {
			break;
		}
		write(1, buf, ret);
	}

	close(newsd);
	close(sd);

	return 0;


	close(newsd);
accept_err:
bind_err:
	close(sd);
socket_err:
	return 1;
}
