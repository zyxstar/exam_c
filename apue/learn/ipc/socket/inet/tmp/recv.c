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
	int val;

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	/* if error */

	val = 1;
	setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
	/* if error */

	myend.sin_family = AF_INET;
	myend.sin_port = SERVER_PORT;
	inet_pton(AF_INET, SERVER_IP, &myend.sin_addr);
	ret = bind(sd, (struct sockaddr *)&myend, sizeof(myend));

	hislen = sizeof(hisend);
	while (1) {
		ret = recvfrom(sd, buf, BUFSIZE, 0, (struct sockaddr *)&hisend, &hislen);
		/* if error */

		write(1, buf, ret);

		cur = time(NULL);
		cur_tm = localtime(&cur);
		ret = strftime(buf, BUFSIZE, "%F %T\n", cur_tm);
		sendto(sd, buf, ret, 0, (struct sockaddr *)&hisend, hislen);
	}

	close(sd);

	return 0;
}
