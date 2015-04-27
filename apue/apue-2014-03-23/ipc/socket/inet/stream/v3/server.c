#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 128

void job(int sd)
{
	char buf[BUFSIZE];
	int ret;

	while (1) {
		ret = read(sd, buf, BUFSIZE);
		if (ret == 0) {
			break;
		}

		write(1, buf, ret);

		/* fix me */
		write(sd, "qnmlgb\n", 7);
	}
}

int main(void)
{
	int sd, newsd;
	struct sockaddr_in myend, hisend;
	socklen_t hislen;
	int ret;
	pid_t pid;
	struct sigaction act;

	act.sa_handler = SIG_DFL;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_NOCLDWAIT;
	sigaction(SIGCHLD, &act, NULL);

	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == -1) {
		perror("socket()");
		return 1;
	}

	myend.sin_family = AF_INET;
	myend.sin_port = htons(8899);
	inet_pton(AF_INET, "192.168.100.93", &myend.sin_addr);
	bind(sd, (struct sockaddr *)&myend, sizeof(myend));
	/* if error */

	listen(sd, 20);
	/* if error */

	hislen = sizeof(hisend);
	while (1) {
		newsd = accept(sd, (struct sockaddr *)&hisend, &hislen);
		pid = fork();
		/* if error */
		if (pid == 0) {
			job(newsd);
			close(newsd);
			close(sd);
			exit(0);
		}

		close(newsd);
	}

	close(sd);

	return 0;
}
