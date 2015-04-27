#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <time.h>
#include <unistd.h>

#include <stdio.h>
#include <errno.h>

#define BUFSIZE 1500

int main(void)
{
	int sd;
	int val;
	struct sockaddr_in myend, hisend;
	socklen_t hislen;
	int ret;
	char buf[BUFSIZE];
	time_t cur;
	struct tm *cur_tm;

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == -1) {
		perror("socket()");
		goto socket_err;
	}

	val = 1;
	setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

	myend.sin_family = AF_INET;
	myend.sin_port = htons(8899);
	//inet_pton(AF_INET, "172.16.30.83", &myend.sin_addr);
	//inet_pton(AF_INET, "0.0.0.0", &myend.sin_addr);
	myend.sin_addr.s_addr = INADDR_ANY;
	ret = bind(sd, (struct sockaddr *)&myend, sizeof(myend));
	if (ret == -1) {
		perror("bind()");
		goto bind_err;
	}

	hislen = sizeof(hisend);
	while (1) {
		ret = recvfrom(sd, buf, BUFSIZE, 0, (struct sockaddr *)&(hisend), &hislen);
		if (ret == -1) {
			if (errno == EINTR) {
				continue;
			}
			perror("recvfrom()");
			break;
		}
		write(1, buf, ret);

		cur = time(NULL);
		cur_tm = localtime(&cur);
		ret = strftime(buf, BUFSIZE, "%F %T\n", cur_tm);
		sendto(sd, buf, ret, 0, (struct sockaddr *)&hisend, hislen);
	}

	close(sd);

	return 0;




bind_err:
	close(sd);
socket_err:
	return 1;
}
