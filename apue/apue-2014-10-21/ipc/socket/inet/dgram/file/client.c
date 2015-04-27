#define _ISOC99_SOURCE
#define _XOPEN_SOURCE

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "comm.h"

#define BUFSIZE   1500

enum CMD {QUIT, DOWNLOAD, LIST};

static int login(int sd, struct sockaddr_in *server_ip, const char *name, const char *pwd)
{
	socklen_t server_len;
	struct packet_st pkt;
	char *encrypt;
	int ret;

	pkt.major = PROTOCOL_MAJOR_LOGIN;
	pkt.minor = 1;
	ret = snprintf(pkt.name, PADSIZE, "%s", name);
	server_len = sizeof(*server_ip);
	sendto(sd, &pkt, ret + 2, 0, (struct sockaddr *)server_ip, server_len);
	/* if error */

	ret = recvfrom(sd, &pkt, sizeof(pkt), 0, (struct sockaddr *)server_ip, &server_len);
	/* if error */
	pkt.salt[ret - 2] = '\0';

	printf("salt: %s\n", pkt.salt);
	encrypt = crypt(pwd, pkt.salt);
	printf("encrypt: %s\n", encrypt);
	ret = snprintf(pkt.encrypt, PADSIZE, "%s", encrypt);

	sendto(sd, &pkt, ret + 2, 0, (struct sockaddr *)server_ip, server_len);

	recvfrom(sd, &pkt, sizeof(pkt), 0, (struct sockaddr *)server_ip, &server_len);
	/* if error */

	if (pkt.ack == 0) {
		connect(sd, (struct sockaddr *)server_ip, server_len);
		/* if error */

		printf("success\n");
		return 0;
	}
	printf("failed\n");
	return -1;
}

static void print_prompt(void)
{
	system("clear");

	printf("%d download\n", DOWNLOAD);
	printf("%d list\n", LIST);
	printf("%d quit\n", QUIT);

	printf("Enter a num: ");
	fflush(stdout);
}

static int getcmd(void)
{
	char buf[BUFSIZE];

	fgets(buf, BUFSIZE, stdin);
	return atoi(buf);
}

static void download(int sd)
{
	char buf[BUFSIZE];
	struct packet_st pkt;
	int ret;
	int fd;
	uint32_t ind;

	printf("Enter file name: ");
	fflush(stdout);
	fgets(buf, BUFSIZE, stdin);
	buf[strlen(buf) - 1] = '\0';

	pkt.major = PROTOCOL_MAJOR_DOWNLOAD;
	pkt.minor = 1;
	ret = snprintf(pkt.path, PADSIZE, "%s", buf);
	write(sd, &pkt, ret + 2);

	ret = read(sd, &pkt, sizeof(pkt));
	if (pkt.minor == 2) {
		return;
	}

	fd = open(buf, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	/* if error */

	write(fd, pkt.data.data, ret - 6);
	ind = ntohl(pkt.data.ind);
	while (1) {
		pkt.minor = 4;
		pkt.data.ind = htonl(ind);
		write(sd, &pkt, 6);

		ret = read(sd, &pkt, sizeof(pkt));
		/* if ind error ??? */
		if (ntohl(pkt.data.ind) == 0) {
			break;
		}
		write(fd, pkt.data.data, ret - 6);
		ind = ntohl(pkt.data.ind);
	}
	pkt.minor = 4;
	pkt.data.ind = htonl(ind);
	write(sd, &pkt, 6);

	close(fd);
}

static void list(int sd)
{
	struct packet_st pkt;
	int ret;
	int i;

	system("clear");

	pkt.major = PROTOCOL_MAJOR_LIST;
	pkt.minor = 1;
	write(sd, &pkt, 2);

	ret = read(sd, &pkt, sizeof(pkt));
	/* if error */
	ret -= 2;
	for (i = 0; i < ret; i++) {
		if (pkt.list[i] == '\0') {
			printf("\n");
		} else {
			printf("%c", pkt.list[i]);
		}
	}
	printf("\n");
	getchar();
}

static void quit(int sd)
{
	struct packet_st pkt;

	pkt.major = PROTOCOL_MAJOR_LOGIN;
	pkt.minor = 100;
	write(sd, &pkt, 2);
}

/* $ ./a.out ip name passwd */
int main(int argc, char **argv)
{
	struct sockaddr_in server_ip;
	char *name = argv[2];
	char *pwd = argv[3];
	int sd;
	int ret;
	int cmd;

	if (argc != 4) {
		fprintf(stderr, "argment...\n");
		return 1;
	}

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	/* if error */

	server_ip.sin_family = AF_INET;
	server_ip.sin_port = SERVER_PORT;
	inet_pton(AF_INET, argv[1], &server_ip.sin_addr);

	ret = login(sd, &server_ip, name, pwd);
	if (ret == -1) {
		fprintf(stderr, "login failed\n");
		return 1;
	}

	while (1) {
		print_prompt();
		cmd = getcmd();
		if (cmd == DOWNLOAD) {
			download(sd);
		} else if (cmd == LIST) {
			list(sd);
		} else if (cmd == QUIT) {
			quit(sd);
			break;
		}
	}

	close(sd);

	return 0;
}
