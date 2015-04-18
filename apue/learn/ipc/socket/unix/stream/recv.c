#define UNIX_PATH_MAX    108

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 32

int main(void)
{
	int sd, newsd;
	struct sockaddr_un myend;
	int ret;
	char buf[BUFSIZE];

	sd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sd == -1) {
		perror("socket()");
		return 1;
	}

	myend.sun_family = AF_UNIX;
	snprintf(myend.sun_path, UNIX_PATH_MAX, "sock_recv");
	unlink(myend.sun_path);
	ret = bind(sd, (struct sockaddr *)&myend, sizeof(myend));
	if (ret == -1) {
		perror("bind()");
		return 1;
	}

	listen(sd, 20);

	newsd = accept(sd, NULL, NULL);
	/* if error */

	while (1) {
		ret = read(newsd, buf, BUFSIZE);
		/* if error */
		if (ret == 0) {
			break;
		}

		write(1, buf, ret);

		write(newsd, "OK\n", 3);
	}

	close(newsd);
	close(sd);

	return 0;
}
