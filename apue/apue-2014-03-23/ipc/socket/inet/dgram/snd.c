#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <errno.h>

#include "comm.h"

#define BUFSIZE 1500

int main(void)
{
	int sd;
	int ret;
	struct sockaddr_in myend, hisend;
	socklen_t hislen;
	char buf[BUFSIZE];

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == -1) {
		perror("socket()");
		return 1;
	}

	hisend.sin_family = AF_INET;
	hisend.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, SERVER_IP, &hisend.sin_addr);
#if 0
	ret = bind(sd, (struct sockaddr *)&myend, sizeof(myend));
	if (ret == -1) {
		perror("bind()");
		close(sd);
		return 1;
	}
#endif

	hislen = sizeof(hisend);
	while (1) {
		ret = read(0, buf, BUFSIZE);
		/* if error */
		if (ret == 0) {
			break;
		}

		sendto(sd, buf, ret, 0, (struct sockaddr *)&hisend, hislen);
		/* if error */

		ret = recvfrom(sd, buf, BUFSIZE, 0, (struct sockaddr *)&hisend, &hislen);
		if (ret == -1) {
			if (errno == EINTR) {
				continue;
			}
			perror("recvfrom()");
			break;
		}

		write(1, buf, ret);
	}

	close(sd);

	return 0;
}
