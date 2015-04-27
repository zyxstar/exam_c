#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <stdio.h>

#define BUFSIZE 1024

int main(void)
{
	int sd;
	struct sockaddr_in hisend;
	int ret;
	char buf[BUFSIZE];

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == -1) {
		perror("socket()");
		goto socket_err;
	}

	hisend.sin_family = AF_INET;
	hisend.sin_port = htons(8899);
	inet_pton(AF_INET, "172.16.30.83", &hisend.sin_addr);
#if 0
	ret = connect(sd, (struct sockaddr *)&hisend, sizeof(hisend));
	if (ret == -1) {
		perror("connect()");
		goto connect_err;
	}
#endif
	while (1) {
		ret = read(0, buf, BUFSIZE);
		/* if error */
		if (ret == 0) {
			break;
		}
		sendto(sd, buf, ret, 0, (struct sockaddr *)&hisend, sizeof(hisend));

		ret = read(sd, buf, BUFSIZE);
		write(1, buf, ret);
	}

	close(sd);

	return 0;


	close(sd);
socket_err:
	return 1;
}
