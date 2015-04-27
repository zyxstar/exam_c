#define UNIX_PATH_MAX    108

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <pthread.h>
#include <termios.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _XOPEN_SOURCE
#include <unistd.h>

#include <protocol.h>
#include <server.h>
#include <debug.h>

#define ENCRYPTSIZE  256

#define BUFSIZE      MSGSIZE
#define SPLIT        15

extern char *crypt(const char *key, const char *salt);

static int sd;
static uint32_t id;
static int local_sd;
static struct sockaddr_un local_addr;

static void input_clear(void)
{
	printf("\033[%d;1H", SPLIT + 1);
	printf("\033[K");
	fflush(stdout);
}

static void input_print(const char *buf, int ind)
{
	int i;

	printf("\033[%d;1H", SPLIT + 1);
	for (i = 0; i < ind; i++) {
		putchar(buf[i]);
	}
	fflush(stdout);
}

static int mygetline(char buf[BUFSIZE])
{
	int i;

	i = 0;
	while (i < BUFSIZE - 1) {
		buf[i] = getchar();
		if (buf[i] == '\n') {
			buf[i] = '\0';
			return i;
		}

		if (buf[i] == 0x7f) { /* 'DEL' */
			i--;
		} else {
			i++;
		}

		input_clear();
		input_print(buf, i);
	}

	buf[BUFSIZE - 1] = '\0';
	return BUFSIZE - 1;
}

static int input2output(int sd, char *buf)
{
	int i;
	char outbuf[BUFSIZE];
	int ret;

	/* message */
	for (i = 0; buf[i] != ':'; i++)
		;

	snprintf(outbuf, BUFSIZE, "me%s", buf + i);

	ret = write(sd, outbuf, strlen(buf + i) + 3);
	if (ret == -1) {
		perror("write(local_sd)");
		fprintf(stderr, "%s\n", local_addr.sun_path);
		sleep(1);
	}
}

static int send_message(const char *buf)
{
	struct packet_st pkt;
	const char *msg;
	int len;

	pkt.major = MAJOR_MESSAGE;
	pkt.minor = 1;
	pkt.msg.dest = htonl(atoi(buf));
	pkt.msg.src = htonl(id);

	for (msg = buf; *msg != ':'; msg++)
		;
	len = snprintf(pkt.msg.message, MSGSIZE, "%s", msg + 1);

	return write(sd, &pkt, msg2pktsize(len));
}

static void send_list_request(void)
{
	struct packet_st pkt;

	pkt.major = MAJOR_LIST;
	pkt.minor = 1;
	pkt.id = htonl(id);

	write(sd, &pkt, 6);
}

static void *input_job(void *unuse)
{
	char buf[BUFSIZE];
	int local_input_sd;
	int ret;

	local_input_sd = socket(AF_LOCAL, SOCK_DGRAM, 0);
	if (local_input_sd == -1) {
		perror("socket(local_input_sd)");
		sleep(1);
	}

	ret = connect(local_input_sd, (struct sockaddr *)&local_addr, sizeof(local_addr));
	if (ret == -1) {
		perror("connect(local_input_sd)");
		sleep(1);
	}

	printf("\033[2J");
	printf("\033[%d;1H", SPLIT);
	printf("------------------------------------------------");
	fflush(stdout);

	while (1) {
		mygetline(buf);
		if (strcmp(buf, "exit") == 0) {
			exit(0);
		}

		input_clear();

		/* list */
		if (strncmp(buf, "list", 4) == 0) {
			send_list_request();
		} else {
			input2output(local_input_sd, buf);
			send_message(buf);
		}
	}

	close(local_input_sd);
}

#define OUTPUT_NUM_MAX 10

struct output_list_node_st {
	char buf[MSGSIZE + 32];
	struct output_list_node_st *prev, *next;
};

struct output_list_st {
	struct output_list_node_st head;
	int num;
};

static void output_clear(void)
{
	int i;

	for (i = 1; i < SPLIT; i++) {
		printf("\033[%d;1H\033[K", i);
	}
	fflush(stdout);
}

static void output_print(struct output_list_st *h)
{
	int i;
	struct output_list_node_st *cur;

	for (i = 1, cur = h->head.next; cur != &h->head; i++, cur = cur->next) {
		printf("\033[%d;1H%s\n", i, cur->buf);
	}
}

static void *output_job(void *unuse)
{
	struct output_list_st head = {{{'\0'}, &head.head, &head.head}, 0};
	int ret;
	struct output_list_node_st *newnode, *tmp;

	while (1) {
		newnode = malloc(sizeof(*newnode));
		/* if error */

		ret = read(local_sd, newnode->buf, MSGSIZE + 32);
		if (ret == -1) {
			perror("read(local_sd,)");
			exit(1);
		}
		newnode->next = &head.head;
		newnode->prev = head.head.prev;
		newnode->next->prev = newnode;
		newnode->prev->next = newnode;
		head.num++;

		if (head.num > OUTPUT_NUM_MAX) {
			tmp = head.head.next;
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			free(tmp);
			head.num--;
		}

		output_clear();
		output_print(&head);
	}
}

static void *recv_job(void *unuse)
{
	struct packet_st pkt;
	int ret, len;
	char buf[BUFSIZE + 32];
	int local_recv_sd;
	int i;

	local_recv_sd = socket(AF_LOCAL, SOCK_DGRAM, 0);
	if (local_recv_sd == -1) {
		perror("socket(local_recv_sd)");
		sleep(1);
	}

	ret = connect(local_recv_sd, (struct sockaddr *)&local_addr, sizeof(local_addr));
	if (ret == -1) {
		perror("connect(local_recv_sd)");
		sleep(1);
	}

	while (1) {
		ret = read(sd, &pkt, sizeof(pkt));

		switch (pkt.major) {
		case MAJOR_MESSAGE:
			/* fix me */
			pkt.msg.message[ret - 10] = '\0';
			ret = snprintf(buf, BUFSIZE + 32, "%d:%s", ntohl(pkt.msg.src), pkt.msg.message);
			ret = write(local_recv_sd, buf, ret);
			debug("%s(), write() return %d\n", __func__, ret);
			if (ret == -1) {
				perror("write()");
			}
			break;
		case MAJOR_LIST:
			for (i = 0; i < (ret - 2) / 4; i++) {
				len = snprintf(buf, BUFSIZE + 32, "%d", ntohl(pkt.list[i]));
				write(local_recv_sd, buf, len);
			}
			break;
		default:
			break;
		}
	}

	close(local_recv_sd);

	return NULL;
}

static void *heart_job(void *unuse)
{
	struct packet_st pkt;

	pkt.major = MAJOR_HEART;
	pkt.minor = 1;
	pkt.id = htonl(id);

	while (1) {
		/* fix me, use select */
		sleep(HEART_INTERVAL);
		write(sd, &pkt, 6);
	}
}

static int start(void)
{
	pthread_t thr_input, thr_output, thr_recv, thr_heart;
	int ret;

	ret = pthread_create(&thr_input, NULL, input_job, NULL);
	if (ret != 0) {
		fprintf(stderr, "pthread_create() failed.\n");
		exit(1);
	}

	ret = pthread_create(&thr_output, NULL, output_job, NULL);
	if (ret != 0) {
		fprintf(stderr, "pthread_create() failed.\n");
		exit(1);
	}

	ret = pthread_create(&thr_recv, NULL, recv_job, NULL);
	if (ret != 0) {
		fprintf(stderr, "pthread_create() failed.\n");
		exit(1);
	}

	ret = pthread_create(&thr_heart, NULL, heart_job, NULL);
	if (ret != 0) {
		fprintf(stderr, "pthread_create() failed.\n");
		exit(1);
	}

	return 0;
}

/* ./client id */
int main(int argc, char **argv)
{
	struct packet_st pkt;
	char pwd[ENCRYPTSIZE];
	char *encrypt;
	struct sockaddr_in server_addr, server_addr_tmp;
	socklen_t hislen = sizeof(server_addr);
	//struct sockaddr_un local_addr;
	int ret;
	struct termios attr;

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

	if (pkt.ack != 0) {
		fprintf(stderr, "login failed.\n");
		exit(1);
	}

	local_sd = socket(AF_LOCAL, SOCK_DGRAM, 0);
	/* if error */

	local_addr.sun_family = AF_UNIX;
	snprintf(local_addr.sun_path, UNIX_PATH_MAX, "./client_socket");
	unlink(local_addr.sun_path);
	ret = bind(local_sd, (struct sockaddr *)&local_addr, sizeof(local_addr));
	if (ret == -1) {
		perror("bind(local)");
		exit(1);
	}

	connect(sd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in));
	/* if error */

	/* set terminal */
	tcgetattr(0, &attr);
	attr.c_lflag &= ~ICANON;
	attr.c_lflag &= ~ECHO;
	attr.c_cc[VMIN] = 1;
	attr.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &attr);

	start();

	while (1) {
		pause();
	}

	close(local_sd);
	close(sd);

	return 0;
}
