#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <stdio.h>

#define BUFSIZE 128

int main(void)
{
	int sd, newsd;
	struct sockaddr_in myend, hisend;
	socklen_t hislen;
	int ret;
	char buf[BUFSIZE];

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

		while (1) {
			ret = read(newsd, buf, BUFSIZE);
			if (ret == 0) {
				break;
			}

			write(1, buf, ret);

			/* fix me */
			write(newsd, "qnmlgb\n", 7);
		}

		close(newsd);
	}

	close(sd);

	return 0;
}
