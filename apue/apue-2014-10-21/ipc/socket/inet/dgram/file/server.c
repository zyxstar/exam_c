#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <signal.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "comm.h"

enum JOBS_STATUS {ST_QUIT, ST_ERROR, ST_RECV, ST_DOWNLOAD, ST_LIST};

#define NAMESIZE     128
#define SALTSIZE     128
#define ENCRYPTSIZE  512
struct pwd_st {
	char name[NAMESIZE];
	char salt[SALTSIZE];
	char encrypt[ENCRYPTSIZE];
};

static void get_name(char name[NAMESIZE], struct packet_st *packet, int packet_len)
{
	int i;

	for (i = 0; i < packet_len - 2; i++) {
		name[i] = packet->name[i];
	}
	name[i] = '\0';
}

static int get_pwdentry(FILE *fp, struct pwd_st *pwd)
{
#define PWDBUFSIZE 1024
	char buf[PWDBUFSIZE];
	char *retp;
	char *last_dollar;
	int i, j;

	retp = fgets(buf, PWDBUFSIZE, fp);
	if (retp == NULL) {
		return -1;
	}

	struct pwd_st {
		char name[NAMESIZE];
		char salt[SALTSIZE];
		char encrypt[ENCRYPTSIZE];
	};
	for (i = 0; ; i++) {
		if (buf[i] == ':') {
			break;
		}
		pwd->name[i] = buf[i];
	}
	pwd->name[i] = '\0';
	i++;
	for (j = 0; buf[i] != '\n'; j++, i++) {
		pwd->encrypt[j] = buf[i];
	}
	pwd->encrypt[j] = '\0';
	last_dollar = strrchr(pwd->encrypt, '$');
	for (i = 0; pwd->encrypt + i <= last_dollar; i++) {
		pwd->salt[i] = pwd->encrypt[i];
	}
	pwd->salt[i] = '\0';

	return 0;
}

static int login(int newsd, struct packet_st *packet, int packet_len)
{
	FILE *fp;
	struct pwd_st pwd;
	char name[NAMESIZE];
	int ret;
	int err;

	fp = fopen("pwd.txt", "r");
	if (fp == NULL) {
		perror("open(pwd.txt)");
		return -1;
	}

	packet->major = PROTOCOL_MAJOR_LOGIN;

	get_name(name, packet, packet_len);
	while (1) {
		ret = get_pwdentry(fp, &pwd);
		if (ret == -1) {
			/* send salt */
			/* if error */
			packet->minor = 2;
			ret = snprintf(packet->salt, PADSIZE, "%s", pwd.salt);
			write(newsd, packet, ret + 2);

			/* recv encrypt */
			ret = read(newsd, packet, sizeof(*packet));

			/* send ACK */
			packet->minor = 10;
			packet->ack = 1;
			write(newsd, packet, 3);

			err = -1;
			break;
		}
		if (strcmp(name, pwd.name) == 0) {
			/* send salt */
			packet->minor = 2;
			ret = snprintf(packet->salt, PADSIZE, "%s", pwd.salt);
			write(newsd, packet, ret + 2);

			/* recv encrypt */
			ret = read(newsd, packet, sizeof(*packet));

			/* send ACK */
			packet->minor = 10;
			if (strncmp(packet->encrypt, pwd.encrypt, strlen(pwd.encrypt)) == 0) {
				packet->ack = 0;
				err = 0;
			} else {
				packet->ack = 1;
				err = -1;
			}
			write(newsd, packet, 3);
			break;
		}
	}

	fclose(fp);
	return err;
}

static void get_path(struct packet_st *packet, int packet_len, char path[4096])
{
	int i;

	for (i = 0; i < packet_len - 2; i++) {
		path[i] = packet->path[i];
	}
	path[i] = '\0';
}

static int download(int newsd, struct packet_st *packet, int packet_len)
{
	int fd;
	char path[4096];
	struct packet_st pkt_r;
	int i;
	int ret;

	packet->major = PROTOCOL_MAJOR_DOWNLOAD;
	get_path(packet, packet_len, path);

	fd = open(path, O_RDONLY);
	if (fd == -1) {
		packet->minor = 2;
		write(newsd, packet, 2);
		return -1;
	}

	packet->minor = 3;
	for (i = 1; ; i++) {
		ret = read(fd, packet->data.data, TRANS_DATASIZE);
		/* if error */
		if (ret == 0) {
			break;
		}

		packet->data.ind = htonl(i);
		write(newsd, packet, ret + 6);
		/* if error */

		/* fix me */
		read(newsd, &pkt_r, sizeof(pkt_r));
		/* if error */
	}
	packet->data.ind = htonl(0);
	write(newsd, packet, 6);
	/* fix me */
	read(newsd, &pkt_r, sizeof(pkt_r));

	close(fd);
	return 0;
}

static int list(int newsd, struct packet_st *packet, int packet_len)
{
	DIR *dir;
	struct dirent *entry;
	int ind;
	int size;
	int ret;

	dir = opendir(".");
	/* if error */

	ind = 0;
	size = PADSIZE;
	while (size > 0) {
		entry = readdir(dir);
		if (entry == NULL) {
			break;
		}
		if (entry->d_name[0] == '.') {
			continue;
		}

		ret = snprintf(packet->list + ind, size, "%s", entry->d_name);
		ind += ret + 1;
		size -= ret + 1;
	}

	closedir(dir);

	packet->major = PROTOCOL_MAJOR_LIST;
	packet->minor = 3;
	write(newsd, packet, 2 + ind - 1);

	return 0;
}

static void jobs(struct packet_st *packet, struct sockaddr_in *his_addr, int packet_len)
{
	int newsd;
	int status = ST_RECV;
	socklen_t hislen;
	int ret;
	int len;

	newsd = socket(AF_INET, SOCK_DGRAM, 0);
	if (newsd == -1) {
		perror("socket(newsd)");
		goto socket_newsd_err;
	}

	ret = connect(newsd, (struct sockaddr *)his_addr, sizeof(*his_addr));
	/* if error */

	ret = login(newsd, packet, packet_len);
	if (ret == -1) {
		goto login_fail;
	}

	hislen = sizeof(*his_addr);
	while (status != ST_QUIT) {
		switch (status) {
		case ST_RECV:
			len = read(newsd, packet, sizeof(*packet));
			if (len == -1) {
				if (errno == EINTR) {
					continue;
				}
				status = ST_ERROR;
				break;
			}
			if (packet->major == PROTOCOL_MAJOR_DOWNLOAD) {
				status = ST_DOWNLOAD;
			} else if (packet->major == PROTOCOL_MAJOR_LIST) {
				status = ST_LIST;
			} else if (packet->major == PROTOCOL_MAJOR_LOGIN && packet->minor == 100) {
				status = ST_QUIT;
			} else {
				status = ST_ERROR;
			}
			break;
		case ST_DOWNLOAD:
			ret = download(newsd, packet, len);
			if (ret == 0) {
				status = ST_RECV;
			} else {
				status = ST_ERROR;
			}
			break;
		case ST_LIST:
			ret = list(newsd, packet, len);
                        if (ret == 0) {
                                status = ST_RECV;
                        } else {
                                status = ST_ERROR;
                        }
			break;
		case ST_ERROR:
			status = ST_QUIT;
			break;
		}
	}

	close(newsd);

	return;


login_fail:
	close(newsd);
socket_newsd_err:
	return;
}

int main(void)
{
	pid_t pid;
	int sd;
	struct sigaction child_act;
	int ret;
	struct sockaddr_in main_addr, his_addr;
	socklen_t hislen;
	struct packet_st packet;

	child_act.sa_handler = SIG_IGN;
	sigemptyset(&child_act.sa_mask);
	child_act.sa_flags = SA_NOCLDWAIT;
	sigaction(SIGCHLD, &child_act, NULL);

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == -1) {
		perror("socket(sd)");
		goto socket_sd_err;
	}

	main_addr.sin_family = AF_INET;
	main_addr.sin_port = SERVER_PORT;
	main_addr.sin_addr.s_addr = INADDR_ANY;
	ret = bind(sd, (struct sockaddr *)&main_addr, sizeof(main_addr));
	if (ret == -1) {
		perror("bind()");
		goto bind_err;
	}

	hislen = sizeof(his_addr);
	while (1) {
		ret = recvfrom(sd, &packet, sizeof(packet), 0, (struct sockaddr *)&his_addr, &hislen);
		if (ret == -1) {
			if (errno == EINTR) {
				continue;
			}
			perror("recvfrom(name)");
			break;
		}

		if (packet.major != PROTOCOL_MAJOR_LOGIN
		    || packet.minor != 1) {
			continue;
		}

		pid = fork();
		/* if error */
		if (pid == 0) {
			jobs(&packet, &his_addr, ret);
			close(sd);
			return 0;
		}
	}

	close(sd);
	return 0;



bind_err:
	close(sd);
socket_sd_err:
	return 1;
}
