#define UNIX_PATH_MAX    108

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>

#include <stdio.h>

#define BUFSIZE 128

int main(void)
{
	int sd;
	struct sockaddr_un myend, hisend;
	socklen_t hislen;
	int ret;
	char buf[BUFSIZE];
	time_t cur;
	struct tm *cur_tm;

	sd = socket(AF_UNIX, SOCK_DGRAM, 0);
	/* if error */

	myend.sun_family = AF_UNIX;
	snprintf(myend.sun_path, UNIX_PATH_MAX, "sock_recv");
	unlink(myend.sun_path);
	ret = bind(sd, (struct sockaddr *)&myend, sizeof(myend));
	if (ret == -1) {
		perror("bind()");
		return 1;
	}

	hislen = sizeof(hisend);
	while (1) {
		ret = recvfrom(sd, buf, BUFSIZE, 0, (struct sockaddr *)&hisend, &hislen);
		write(1, buf, ret);

		cur = time(NULL);
		cur_tm = localtime(&cur);
		ret = strftime(buf, BUFSIZE, "%F %T\n", cur_tm);
		sendto(sd, buf, ret, 0, (struct sockaddr *)&hisend, hislen);
	}

	close(sd);

	return 0;
}
