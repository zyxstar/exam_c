#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define BUFSIZE 1024

static void jobs(int newsd)
{
	char buf[BUFSIZE];
	time_t cur;
	struct tm *cur_tm;
	int ret;

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
}

int main(void)
{
	int sd, newsd;
	struct sockaddr_in myend, hisend;
	socklen_t hislen;
	int ret;
	pid_t pid;

	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == -1) {
		perror("socket()");
		goto socket_err;
	}

	myend.sin_family = AF_INET;
	myend.sin_port = 8899;	/* fixme */
	inet_pton(AF_INET, "172.16.30.83", &myend.sin_addr);
	ret = bind(sd, (struct sockaddr *)&myend, sizeof(myend));
	if (ret == -1) {
		perror("bind()");
		goto bind_err;
	}

	listen(sd, 20);

	hislen = sizeof(hisend); /* warning: must init */
	while (1) {
		newsd = accept(sd, (struct sockaddr *)&hisend, &hislen);
		if (newsd == -1) {
			perror("accept()");
			break;
		}

		pid = fork();
		if (pid == -1) {
			perror("fork()");
			close(newsd);
			continue;
		}
		if (pid == 0) {
			jobs(newsd);
			close(newsd);
			close(sd);
			exit(0);
		}

		close(newsd);
	}

	printf("\033[31mbreak\033[0m\n");
	close(sd);

	return 0;

read_newsd_err:
bind_err:
	close(sd);
socket_err:
	return 1;
}
