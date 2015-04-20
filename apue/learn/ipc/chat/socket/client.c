
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _XOPEN_SOURCE
#include <unistd.h>

#include <protocol.h>
#include <server.h>
#include <debug.h>

#define ENCRYPTSIZE  256

/* ./client id */
int main(int argc, char **argv)
{
	uint32_t id;
	struct packet_st pkt;
	char pwd[ENCRYPTSIZE];
	char *encrypt;
	int sd;
	struct sockaddr_in server_addr, server_addr_tmp;
	socklen_t hislen = sizeof(server_addr);
	int ret;

	if (argc != 2) {
		fprintf(stderr, "client id\n");
		return 1;
	}

	printf("input passwd: ");
	fflush(stdout);
	fgets(pwd, ENCRYPTSIZE, stdin);
	pwd[strlen(pwd) - 1] = '\0';

	id = atoi(argv[1]);

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	/* if error */

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = SERVER_PORT;
	inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

	pkt.major = MAJOR_LOGIN;
	pkt.minor = 1;
	pkt.id = htonl(id);

	sendto(sd, &pkt, 6, 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
	/* if error */

	ret = recvfrom(sd, &pkt, sizeof(pkt), 0, (struct sockaddr *)&server_addr_tmp, &hislen);

	pkt.salt[ret - 2] = '\0';
	encrypt = crypt(pwd, pkt.salt);

	debug("salt: %s\n", pkt.salt);
	debug("encrypt: %s\n", encrypt);

	ret = snprintf(pkt.encrypt, ENCRYPTSIZE, "%s", encrypt);
	sendto(sd, &pkt, ret + 2, 0, (struct sockaddr *)&server_addr_tmp, sizeof(server_addr_tmp));
	/* if error */

	recvfrom(sd, &pkt, sizeof(pkt), 0, NULL, NULL);
	/* if error */

	printf("ACK: %d\n", pkt.ack);

	close(sd);

	return 0;
}
