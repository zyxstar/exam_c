#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <pthread.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <protocol.h>
#include <server.h>
#include <database.h>
#include <debug.h>

enum SERVER_STATUS {ST_QUIT, ST_ERROR, ST_RECV, ST_LOGIN, ST_MSG, ST_LIST, ST_HEART};

#define SALTSIZE     64
#define ENCRYPTSIZE  256

struct shadow_st {
	uint32_t id;
	char salt[SALTSIZE];
	char encrypt[ENCRYPTSIZE];
};

/* return if (id exist) */
static int get_shadow(uint32_t id, struct shadow_st *sdw)
{
	FILE *fp;
	char buf[PADSIZE];
	char *retp;
	char *p;
	int i;
	int count;

	sdw->id = id;
	snprintf(sdw->salt, SALTSIZE, "$6$Cb0AuRNL$");
	snprintf(sdw->encrypt, ENCRYPTSIZE, "$6$Cb0AuRNL$ABCD");

	fp = fopen("shadow.txt", "r");
	if (fp == NULL) {
		return 0;
	}

	while (1) {
		retp = fgets(buf, PADSIZE, fp);
		if (retp == NULL) {
			break;
		}
		buf[strlen(buf) - 1] = '\0';

		sdw->id = atoi(buf);
		if (sdw->id != id) {
			continue;
		}

		for (p = buf; *p != ':'; p++)
			;
		p++;
		snprintf(sdw->encrypt, ENCRYPTSIZE, "%s", p);
		for (i = 0, count = 0; ; p++, i++) {
			sdw->salt[i] = *p;
			if (*p == '$') {
				count++;
			}
			if (count == 3) {
				sdw->salt[i + 1] = '\0';
				fclose(fp);
				return 1;
			}
		}
	}

	fclose(fp);

	return 0;
}

static int login_job(int sd, struct packet_st *pkt_r, int recv_len, struct sockaddr_in *hisend)
{
	uint32_t id;
	struct shadow_st sdw;
	int ret;
	int id_exist;
	struct packet_st pkt;
	struct database_record_st record, *recordp;

	debug("call %s\n", __func__);

	char ip_buf[32];
	inet_ntop(AF_INET, &hisend->sin_addr, ip_buf, 32);
	debug("in %s(), hisip: %s, hisport: %d\n", __func__, ip_buf, ntohs(hisend->sin_port));

	/* check minor */
	id = ntohl(pkt_r->id);

	id_exist = get_shadow(id, &sdw);

	debug("in %s(), %d, %s\n%s\n", __func__, sdw.id, sdw.salt, sdw.encrypt);

	ret = snprintf(pkt.salt, PADSIZE, "%s", sdw.salt);
	pkt.major = MAJOR_LOGIN;
	pkt.minor = 2;
	/* timeout ? */
	debug("in %s(), will sendto, ret = %d\n", __func__, ret);
	ret = sendto(sd, &pkt, ret + 2, 0, (struct sockaddr *)hisend, sizeof(*hisend));
	debug("in %s(), sendto() return %d\n", __func__, ret);
	perror("sendto()");

	ret = recvfrom(sd, &pkt, sizeof(pkt), 0, NULL, NULL);
	/* check src addr, major, minor */
	pkt.encrypt[ret - 2] = '\0';
	debug("%s\n%s\n", pkt.encrypt, sdw.encrypt);
	if (id_exist == 0 || strcmp(pkt.encrypt, sdw.encrypt) != 0) {
		/* fail */
		pkt.major = MAJOR_LOGIN;
		pkt.minor = 4;
		pkt.ack = 1;
		sendto(sd, &pkt, 3, 0, (struct sockaddr *)hisend, sizeof(*hisend));
	} else {
		/* success */
		pkt.major = MAJOR_LOGIN;
		pkt.minor = 4;
		pkt.ack = 0;

		/* update database */
		recordp = database_find(id);
		if (recordp == NULL) {
			record.id = id;
			memcpy(&record.addr, hisend, sizeof(struct sockaddr_in));
			record.last = time(NULL);
			record.online = 1;
			database_insert(&record);
			/* if error */
		} else {
			memcpy(&recordp->addr, hisend, sizeof(struct sockaddr_in));
                        recordp->last = time(NULL);
                        recordp->online = 1;
		}

		sendto(sd, &pkt, 3, 0, (struct sockaddr *)hisend, sizeof(*hisend));
	}

	return 0;
}

struct login_info {
	int sd;
	struct packet_st pkt_r;
	int recv_len;
	struct sockaddr_in hisend;
};

static void *login_thread(void *l_info)
{
	struct login_info *info = l_info;
	int newsd;

	pthread_detach(pthread_self());

	newsd = socket(AF_INET, SOCK_DGRAM, 0);
	if (newsd == -1) {
		/* fix me, send error to client */
		debug("in %s(), socket(newsd) failed\n", __func__);
		return NULL;
	}

	login_job(newsd, &info->pkt_r, info->recv_len, &info->hisend);
	/* if error */

	close(newsd);
	free(info);

	return NULL;
}

static int login(int sd, struct packet_st *pkt_r, int recv_len, struct sockaddr_in *hisend)
{
	pthread_t tid;
	struct login_info *info;
	int ret;
	uint32_t id;
	struct database_record_st *record;

	debug("call %s\n", __func__);

	if (pkt_r->minor == 50) {
		id = ntohl(pkt_r->id);
		record = database_find(id);
		if (record == NULL) {
			return -1;
		}
		record->online = 0;
		return 0;
	}

	info = malloc(sizeof(*info));
	if (info == NULL) {
		return -1;
	}

	info->sd = sd;
	info->pkt_r = *pkt_r;
	info->recv_len = recv_len;
	info->hisend = *hisend;

	char ip_buf[32];
	inet_ntop(AF_INET, &hisend->sin_addr, ip_buf, 32);
	debug("in %s(), hisip: %s, hisport: %d\n", __func__, ip_buf, ntohs(hisend->sin_port));

	ret = pthread_create(&tid, NULL, login_thread, info);
	if (ret) {
		return -1;
	}
	return 0;
}

static int online(struct database_record_st *record)
{
	time_t cur;

	if (record->online == 0) {
		return 0;
	}

	cur = time(NULL);
	if (cur - record->last > OFFLINE_INTERVAL) {
		return 0;
	}

	return 1;
}

static int message(int sd, struct packet_st *pkt_r, int recv_len, struct sockaddr_in *hisend)
{
	uint32_t dest;
	struct database_record_st *record;

	debug("call %s()\n", __func__);

	dest = ntohl(pkt_r->msg.dest);
	record = database_find(dest);
	if (record == NULL) {
		return -1;
	}

	if (!online(record)) {
		return -1;
	}

	return sendto(sd, pkt_r, recv_len, 0, (struct sockaddr *)&record->addr, sizeof(record->addr));
}

static int list(int sd, struct packet_st *pkt_r, int recv_len, struct sockaddr_in *hisend)
{
	struct packet_st pkt;
	int ret;
	int i;

	ret = database_getlist(pkt.list, LISTNUM);

	for (i = 0; i < ret; i++) {
		pkt.list[i] = htonl(pkt.list[i]);
	}

	pkt.major = MAJOR_LIST;
	pkt.minor = 2;
	return sendto(sd, &pkt, 2 + ret * 4, 0, (struct sockaddr *)hisend, sizeof(*hisend));
}

static int heart(int sd, struct packet_st *pkt_r, int recv_len, struct sockaddr_in *hisend)
{
	struct database_record_st *record;

	record = database_find(ntohl(pkt_r->id));
	if (record == NULL) {
		return -1;
	}

	/* check addr and online */

	record->last = time(NULL);
}

int main(void)
{
	int status;
	int sd;
	struct packet_st pkt;
	struct sockaddr_in myend, hisend;
	socklen_t hislen;
	int val;
	int ret;
	int recv_len;

	database_init();

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == -1) {
		perror("socket()");
		goto socket_err;
	}

	val = 1;
	setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

	myend.sin_family = AF_INET;
	myend.sin_port = SERVER_PORT;
	myend.sin_addr.s_addr = INADDR_ANY;
	ret = bind(sd, (struct sockaddr *)&myend, sizeof(myend));
	if (ret == -1) {
		perror("bind()");
		goto bind_err;
	}

	hislen = sizeof(hisend);
	status = ST_RECV;
	while (status != ST_QUIT) {
		switch (status) {
		case ST_RECV:
			recv_len = recvfrom(sd, &pkt, sizeof(pkt), 0, (struct sockaddr *)&hisend, &hislen);
			if (recv_len == -1) {
				status = ST_ERROR;
				break;
			}
			if (pkt.major == MAJOR_LOGIN) {
				status = ST_LOGIN;
			} else if (pkt.major == MAJOR_MESSAGE) {
				status = ST_MSG;
			} else if (pkt.major == MAJOR_LIST) {
				status = ST_LIST;
			} else if (pkt.major == MAJOR_HEART) {
				status = ST_HEART;
			} else if (pkt.major == MAJOR_MANAGE) {
				/* fix me */
				status = ST_RECV;
			} else if (pkt.major == MAJOR_ERROR) {
				status = ST_ERROR;
			} else {
				status = ST_ERROR;
			}
			break;
		case ST_LOGIN:
			ret = login(sd, &pkt, recv_len, &hisend);
			if (ret == 0) {
				status = ST_RECV;
			} else {
				status = ST_ERROR;
			}
			break;
		case ST_MSG:
			message(sd, &pkt, recv_len, &hisend);
			status = ST_RECV;
			break;
		case ST_LIST:
			list(sd, &pkt, recv_len, &hisend);
			status = ST_RECV;
			break;
		case ST_HEART:
			heart(sd, &pkt, recv_len, &hisend);
                        status = ST_RECV;
			break;
		case ST_ERROR:
			/* fix me */
			status = ST_QUIT;
			break;
		}
	}

	close(sd);
	database_destroy();

	return 0;




bind_err:
	close(sd);
socket_err:
	database_destroy();
	return 1;
}
