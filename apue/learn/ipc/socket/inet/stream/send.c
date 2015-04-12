#include  <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#include <stdio.h>

#include "comm.h"

#define BUFSIZE  64

int main(void)
{
	int sd;
	int ret;
	struct sockaddr_in hisend;
	socklen_t hislen;
	char buf[BUFSIZE];

	sd = socket(AF_INET, SOCK_STREAM, 0);
	/* if error */

	hisend.sin_family = AF_INET;
	hisend.sin_port = SERVER_PORT;
	inet_pton(AF_INET, SERVER_IP, &hisend.sin_addr);
	ret = connect(sd, (struct sockaddr *)&hisend, sizeof(hisend));
	if (ret == -1) {
		perror("connect()");
		close(sd);
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
