#define _XOPEN_SOURCE

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "protocol.h"
#include "server.h"

int snprintf(char *str, size_t size, const char *format, ...);

static int login(int sd, uint32_t id, char *pwd)
{
	struct packet_st pkt;
	struct sockaddr_in hisend;
	socklen_t hislen;
	char *encrypt;
	int ret;

	pkt.major = 1;
	pkt.minor = 1;
	pkt.id = htonl(id);

	hisend.sin_family = AF_INET;
	hisend.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, SERVER_IP, &hisend.sin_addr);
	sendto(sd, &pkt, 6, 0, (struct sockaddr *)&hisend, sizeof(hisend));

	hislen = sizeof(hisend);
	recvfrom(sd, &pkt, sizeof(pkt), 0, (struct sockaddr *)&hisend, &hislen);

	encrypt = crypt(pwd, pkt.salt);
	ret = snprintf(pkt.encrypt, PAD_SIZE, "%s", encrypt);
	sendto(sd, &pkt, ret + 2, 0, (struct sockaddr *)&hisend, hislen);

	recvfrom(sd, &pkt, sizeof(pkt), 0, NULL, NULL);
	if (pkt.ack == 0) {
		return 0;
	} else {
		return -1;
	}
}

#define BUFSIZE 1024

/* $ client id passwd */
int main(int argc, char **argv)
{
	int sd;
	struct sockaddr_in hisend;
	int ret;
	pid_t pid;
	struct packet_st pkt;
	uint32_t id;
	char *retp;
	char buf[BUFSIZE];

	if (argc != 3) {
		fprintf(stderr, "argment...\n");
		return 1;
	}

	id = atoi(argv[1]);

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	/* if error */

	ret = login(sd, id, argv[2]);
	if (ret == -1) {
		fprintf(stderr, "login() failed.\n");
		close(sd);
		return 1;
	}

	pid = fork();
	/* if error */
	if (pid == 0) {
		while (1) {
			ret = recvfrom(sd, &pkt, sizeof(pkt), 0, NULL, NULL);
			write(1, "\033[31m", 5);
			write(1, pkt.msg.message, ret - 10);
			write(1, "\n\033[0m", 5);
		}

		return 0;
	}

	hisend.sin_family = AF_INET;
	hisend.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, SERVER_IP, &hisend.sin_addr);
	pkt.msg.src = htonl(id);
	while (1) {
		/* id:msg */
		retp = fgets(buf, BUFSIZE, stdin);
		sscanf(buf, "%d:%s\n", &pkt.msg.dest, pkt.msg.message);

		pkt.msg.dest = htonl(pkt.msg.dest);
		pkt.major = 2;
		pkt.minor = 1;
		sendto(sd, &pkt, strlen(pkt.msg.message) + 10, 0, (struct sockaddr *)&hisend, sizeof(hisend));
	}

	close(sd);

	return 0;
}
