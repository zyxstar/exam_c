#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define BUFSIZE 1024

static void jobs(int sd)
{
	int newsd;
	char buf[BUFSIZE];
	time_t cur;
	struct tm *cur_tm;
	socklen_t hislen;
	struct sockaddr_in hisend;
	int ret;

	hislen = sizeof(hisend); /* warning: must init */
	while (1) {
		newsd = accept(sd, (struct sockaddr *)&hisend, &hislen);
		if (newsd == -1) {
			perror("accept()");
			break;
		}

		while (1) {
			ret = read(newsd, buf, BUFSIZE);
			if (ret == -1) {
				if (errno == EINTR) {
					printf("\033[31mEINTR\033[0m\n");
					continue;
				}
				break;
			}
			if (ret == 0) {
				break;
			}
			write(1, buf, ret);

			cur = time(NULL);
			cur_tm = localtime(&cur);
			ret = strftime(buf, BUFSIZE, "%F %T\n", cur_tm);
			printf("before write\n");
			write(newsd, buf, ret);
			printf("after write\n");
		}

		close(newsd);
	}
}

int main(void)
{
	int sd;
	struct sockaddr_in myend;
	int ret;
	int i;
	pid_t pid;
	int val;

	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == -1) {
		perror("socket()");
		goto socket_err;
	}

	val = 1;
	setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

	myend.sin_family = AF_INET;
	myend.sin_port = 8899;	/* fixme */
	inet_pton(AF_INET, "172.16.30.83", &myend.sin_addr);
	ret = bind(sd, (struct sockaddr *)&myend, sizeof(myend));
	if (ret == -1) {
		perror("bind()");
		goto bind_err;
	}

	listen(sd, 20);

	for (i = 0; i < 2; i++) {
		pid = fork();
		if (pid == -1) {
			/* error */
		}
		if (pid == 0) {
			jobs(sd);
			close(sd);
			exit(0);
		}
	}

	close(sd);

	while (1) {
		pause();
	}

	return 0;

read_newsd_err:
bind_err:
	close(sd);
socket_err:
	return 1;
}
