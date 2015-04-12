#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <time.h>

#include <stdio.h>

#include "comm.h"

#define BUFSIZE  64

int main(void)
{
	int sd, newsd;
	int ret;
	struct sockaddr_in myend, hisend;
	socklen_t hislen;
	char buf[BUFSIZE];
	time_t cur;
	struct tm *cur_tm;

	sd = socket(AF_INET, SOCK_STREAM, 0);
	/* if error */

	myend.sin_family = AF_INET;
	myend.sin_port = SERVER_PORT;
	inet_pton(AF_INET, SERVER_IP, &myend.sin_addr);
	ret = bind(sd, (struct sockaddr *)&myend, sizeof(myend));
	if (ret == -1) {
		perror("bind()");
		close(sd);
		return 1;
	}

	listen(sd, 20);

	hislen = sizeof(hisend); /* must init */
	newsd = accept(sd, (struct sockaddr *)&hisend, &hislen);
	/* if error */

	while (1) {
		ret = read(newsd, buf, BUFSIZE);
		/* if error */
		if (ret == 0) {
			break;
		}

		write(1, buf, ret);

		cur = time(NULL);
		cur_tm = localtime(&cur);
		ret = strftime(buf, BUFSIZE, "%F %T\n", cur_tm);
		write(newsd, buf, ret);
	}

	close(newsd);
	close(sd);

	return 0;
}
