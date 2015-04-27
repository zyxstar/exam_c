#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#include <stdio.h>

#define BUFSIZE 1024

int main(void)
{
	int sd, newsd;
	struct sockaddr_in myend, hisend;
	socklen_t hislen;
	int ret;
	char buf[BUFSIZE];
	time_t cur;
	char *timep;

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
	newsd = accept(sd, (struct sockaddr *)&hisend, &hislen);

	/* fix me */
	while (1) {
		ret = read(newsd, buf, BUFSIZE);
		/* if error */
		if (ret == 0) {
			break;
		}
		write(1, buf, ret);

		cur = time(NULL);
		timep = ctime(&cur);
		ret = snprintf(buf, BUFSIZE, "%s\n", timep);
		write(newsd, buf, ret);
	}

	close(newsd);
	close(sd);

	return 0;


bind_err:
	close(sd);
socket_err:
	return 1;
}
