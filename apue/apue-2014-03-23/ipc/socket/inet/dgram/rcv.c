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
	int val;

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == -1) {
		perror("socket()");
		return 1;
	}

	val = 1;
        setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

	myend.sin_family = AF_INET;
	myend.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, SERVER_IP, &myend.sin_addr);
	ret = bind(sd, (struct sockaddr *)&myend, sizeof(myend));
	if (ret == -1) {
		perror("bind()");
		close(sd);
		return 1;
	}

	hislen = sizeof(hisend);
	while (1) {
		ret = recvfrom(sd, buf, BUFSIZE, 0, (struct sockaddr *)&hisend, &hislen);
		if (ret == -1) {
			if (errno == EINTR) {
				continue;
			}
			perror("recvfrom()");
			break;
		}

		write(1, buf, ret);
		sendto(sd, "qnmlgb\n", 7, 0, (struct sockaddr *)&hisend, hislen);
		/* if error */
	}

	close(sd);

	return 0;
}
