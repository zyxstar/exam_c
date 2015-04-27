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
	setsockopt(sd, SOL_SOCKET, SO_BROADCAST, &val, sizeof(val));

	setsockopt(sd, SOL_SOCKET, SO_BINDTODEVICE, "eth0", 5);

	hisend.sin_family = AF_INET;
	hisend.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, "255.255.255.255", &hisend.sin_addr);

	hislen = sizeof(hisend);
	while (1) {
		ret = read(0, buf, BUFSIZE);
		/* if error */
		if (ret == 0) {
			break;
		}

		sendto(sd, buf, ret, 0, (struct sockaddr *)&hisend, hislen);
		/* if error */
	}

	close(sd);

	return 0;
}
