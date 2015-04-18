#define UNIX_PATH_MAX    108

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <stdio.h>

#define BUFSIZE 128

int main(void)
{
	int sd;
	struct sockaddr_un myend, hisend;
	int ret;
	char buf[BUFSIZE];

	sd = socket(AF_UNIX, SOCK_DGRAM, 0);
	/* if error */

	hisend.sun_family = AF_UNIX;
	snprintf(hisend.sun_path, UNIX_PATH_MAX, "sock_recv");

	myend.sun_family = AF_UNIX;
	snprintf(myend.sun_path, UNIX_PATH_MAX, "sock_send");
	unlink(myend.sun_path);
	ret = bind(sd, (struct sockaddr *)&myend, sizeof(myend));
	if (ret == -1) {
		perror("bind()");
		return 1;
	}

	while (1) {
		ret = read(0, buf, BUFSIZE);
		/* if error */
		if (ret == 0) {
			break;
		}

		sendto(sd, buf, ret, 0, (struct sockaddr *)&hisend, sizeof(hisend));

		ret = read(sd, buf, BUFSIZE);
		write(1, buf, ret);
	}

	close(sd);

	return 0;
}
