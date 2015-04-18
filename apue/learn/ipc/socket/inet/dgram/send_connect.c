#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <time.h>

#include <stdio.h>

#include "comm.h"

#define BUFSIZE   128

int main(void)
{
	int sd;
	struct sockaddr_in myend, hisend;
	socklen_t hislen;
	time_t cur;
	struct tm *cur_tm;
	char buf[BUFSIZE];
	int ret;

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	/* if error */

	hisend.sin_family = AF_INET;
	hisend.sin_port = SERVER_PORT;
	inet_pton(AF_INET, SERVER_IP, &hisend.sin_addr);
	ret = connect(sd, (struct sockaddr *)&hisend, sizeof(hisend));
	/* if error */

	hislen = sizeof(hisend);
	while (1) {
		ret = read(0, buf, BUFSIZE);
		/* if error */
		if (ret == 0) {
			break;
		}

		write(sd, buf, ret);

		ret = read(sd, buf, BUFSIZE);
		/* if error */

		write(1, buf, ret);
	}

	close(sd);

	return 0;
}
