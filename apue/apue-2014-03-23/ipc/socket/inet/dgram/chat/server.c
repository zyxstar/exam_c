#include <pthread.h>

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
#include "db.h"

#define ENCRYPT_SIZE 1024

enum STATUS {
	STAT_QUIT,
	STAT_RECV,
	STAT_LOGIN,
	STAT_MESSAGE,
	STAT_ERROR,
};

struct job_arg {
	struct sockaddr_in hisend;
	struct packet_st pkt;
};

static DB *db;

static int get_encrypt(unsigned long id, char encrypt[ENCRYPT_SIZE])
{
	FILE *fp;
	unsigned long line_id;
	char *retp;
	int len;

	fp = fopen("shadow", "r");
	/* if error */

	while (1) {
		retp = fgets(encrypt, ENCRYPT_SIZE, fp);
		if (retp == NULL) {
			break;
		}

		sscanf(encrypt, "%lu:$", &line_id);
		if (line_id == id) {
			len = strlen(encrypt);
			if (encrypt[len - 1] == '\n') {
				encrypt[len - 1] = '\0';
				len--;
			}
			retp = strchr(encrypt, ':');
			retp++;

			memmove(encrypt, retp, len + 1 - (retp - encrypt));

			fclose(fp);
			return 0;
		}
	}

	fclose(fp);
	return -1;
}

static int get_salt(char *encrypt, char *salt)
{
	char *p;
	int i;
	int count;

	p = strchr(encrypt, '$');
	for (i = 0, count = 0; ; i++) {
		salt[i] = p[i];
		if (p[i] == '$') {
			count++;
		}
		if (count == 3) {
			break;
		}
	}
	i++;
	salt[i] = '\0';
	return i;
}

static int pwd_match(struct packet_st *pkt, int pkt_len, char *encrypt)
{
	return !strncmp((char *)pkt->encrypt, encrypt, pkt_len - 2);
}

static void *login_job(void *job_arg)
{
	struct job_arg *arg = job_arg;
	int sd;
	struct packet_st pkt;
	int len;
	char encrypt[ENCRYPT_SIZE];
	struct db_data_st data;
	int ret;

	pthread_detach(pthread_self());

	get_encrypt(ntohl(arg->pkt.id), encrypt);

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == -1) {
		perror("socket()");
		goto socket_err;
	}

	pkt.major = MA_LOGIN;
	pkt.minor = 2;
	len = get_salt(encrypt, (char *)pkt.salt);

	sendto(sd, &pkt, len + 2, 0, (struct sockaddr *)&arg->hisend, sizeof(arg->hisend));
	/* if error */

	ret = recvfrom(sd, &pkt, sizeof(pkt), 0, NULL, NULL);
	if (pwd_match(&pkt, ret, encrypt)) {
		data.id = ntohl(arg->pkt.id);
		data.addr = arg->hisend;
		db_insert(db, &data);
		/* if error */

		pkt.major = 1;
		pkt.minor = 4;
		pkt.ack = 0;
		sendto(sd, &pkt, 3, 0, (struct sockaddr *)&arg->hisend, sizeof(arg->hisend));
	} else {
		pkt.major = 1;
		pkt.minor = 4;
		pkt.ack = 1;
		sendto(sd, &pkt, 3, 0, (struct sockaddr *)&arg->hisend, sizeof(arg->hisend));
	}

	close(sd);
	return NULL;


	close(sd);
socket_err:
	return NULL;
}

static int login(struct sockaddr_in *hisend, struct packet_st *pkt)
{
	pthread_t tid;
	struct job_arg arg;
	arg.hisend = *hisend;
	arg.pkt = *pkt;

	return pthread_create(&tid, NULL, login_job, &arg);
}

void message(int sd, struct packet_st *pkt, int len)
{
	struct db_data_st *data;

	data = db_search(db, ntohl(pkt->msg.dest));
	if (data == NULL) {
		return;
	}

	sendto(sd, pkt, len, 0, (struct sockaddr *)&data->addr, sizeof(struct sockaddr_in));
}

int main(void)
{
	struct packet_st pkt;
	int status;
	int sd;
	int ret;
	int val;
	struct sockaddr_in myend, hisend;
	socklen_t hislen;
	int pktlen;

	db = db_creat();
	/* if error */

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == -1) {
		perror("socket()");
		goto socket_err;
	}

	val = 1;
	setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
	/* if error */

	myend.sin_family = AF_INET;
	myend.sin_port = htons(SERVER_PORT);
	myend.sin_addr.s_addr = INADDR_ANY;
	ret = bind(sd, (struct sockaddr *)&myend, sizeof(myend));
	if (ret == -1) {
		perror("bind()");
		goto bind_err;
	}

	hislen = sizeof(hisend);
	status = STAT_RECV;
	while (status != STAT_QUIT) {
		switch (status) {
		case STAT_RECV:
			pktlen = recvfrom(sd, &pkt, sizeof(pkt), 0, (struct sockaddr *)&hisend, &hislen);
			if (pktlen == -1) {
				if (errno == EINTR) {
					continue;
				}
				status = STAT_ERROR;
				break;
			}
			switch (pkt.major) {
			case MA_LOGIN:
				status = STAT_LOGIN;
				break;
			case MA_MESSAGE:
				status = STAT_MESSAGE;
				break;
			case MA_ERROR:
				status = STAT_ERROR;
				break;
			}
			break;
		case STAT_LOGIN:
			ret = login(&hisend, &pkt);
			if (ret == 0) {
				status = STAT_RECV;
			} else {
				status = STAT_ERROR;
			}
			break;
		case STAT_MESSAGE:
			message(sd, &pkt, pktlen);
			status = STAT_RECV;
			break;
		case STAT_ERROR:
			status = STAT_QUIT;
			break;
		}
	}

	close(sd);
	db_destroy(db);

	return 0;



bind_err:
	close(sd);
socket_err:
	db_destroy(db);
	return 1;
}
