#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <stdio.h>

#define BUFSIZE 128

int main(void)
{
	int sd;
	struct sockaddr_in myend, hisend;
	socklen_t hislen;
	int ret;
	char buf[BUFSIZE];

	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == -1) {
		perror("socket()");
		return 1;
	}

	hisend.sin_family = AF_INET;
	hisend.sin_port = htons(8899);
	inet_pton(AF_INET, "192.168.100.93", &hisend.sin_addr);
	connect(sd, (struct sockaddr *)&hisend, sizeof(hisend));
	/* if error */

	while (1) {
		ret = read(0, buf, BUFSIZE);
		if (ret == 0) {
			break;
		}

		/* fix me */
		write(sd, buf, ret);

		ret = read(sd, buf, BUFSIZE);
		if (ret == 0) {
                        break;
                }

		write(1, buf, ret);
	}

	close(sd);

	return 0;
}
