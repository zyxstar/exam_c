#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/socket.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define BUFSIZE 1024

#define PROC_TOTAL_MAX  8
#define PROC_FREE_MIN   2
#define PROC_FREE_MAX   6
#define PROC_PER_FORK   3
#define TIMES_MAX       2

enum MSG_STATUS {ST_QUIT, ST_FREE, ST_BUSY, ST_NOTHING};

struct msgbuf_st {
	long dest;		/* dest id */
	long src;		/* src id */
	long status;		/* current status */
};

static int min(int a, int b)
{
	return a < b ? a : b;
}

static void jobs(int sd, int msgid);

static void remain_proc(int sd, int msgid, int *proc_nr, int *proc_free_nr)
{
	int num;
	int i;
	pid_t pid;

	if (*proc_free_nr < PROC_FREE_MIN) {
		num = min(PROC_PER_FORK, PROC_TOTAL_MAX - *proc_nr);
		for (i = 0; i < num; i++) {
			pid = fork();
			/* fix me */
			/* if error */
			if (pid == 0) {
				jobs(sd, msgid);
				exit(0);
			}
		}
		*proc_nr += i;
		*proc_free_nr += i;
	}
}

static void jobs(int sd, int msgid)
{
	int newsd;
	char buf[BUFSIZE];
	time_t cur;
	struct tm *cur_tm;
	socklen_t hislen;
	struct sockaddr_in hisend;
	int ret;
	struct msgbuf_st msgbuf_r, msgbuf_s;
	int times = 0;
	long myid = getpid();

	printf("myid = %ld\n", myid);

	msgbuf_s.dest = 1;
	msgbuf_s.src = myid;

	hislen = sizeof(hisend); /* warning: must init */
	for (times = 1; ; times++) {
		newsd = accept(sd, (struct sockaddr *)&hisend, &hislen);
		if (newsd == -1) {
			perror("accept()");
			break;
		}
		msgbuf_s.status = ST_BUSY;
		msgsnd(msgid, &msgbuf_s, sizeof(long) * 2, 0);

		while (1) {
			ret = read(newsd, buf, BUFSIZE);
			if (ret == -1) {
				if (errno == EINTR) {
					printf("\033[31mEINTR\033[0m\n");
					continue;
				}
				break;
			}
			if (ret == 0) {
				break;
			}
			write(1, buf, ret);

			cur = time(NULL);
			cur_tm = localtime(&cur);
			ret = strftime(buf, BUFSIZE, "%F %T\n", cur_tm);
			write(newsd, buf, ret);
		}

		close(newsd);

		if (times >= TIMES_MAX) {
			msgbuf_s.status = ST_QUIT;
			msgsnd(msgid, &msgbuf_s, sizeof(long) * 2, 0);
			break;
		}
		msgbuf_s.status = ST_FREE;
		msgsnd(msgid, &msgbuf_s, sizeof(long) * 2, 0);
		msgrcv(msgid, &msgbuf_r, sizeof(long) * 2, myid, 0);
		if (msgbuf_r.status == ST_QUIT) {
			break;
		}
	}
}

int main(void)
{
	int sd;
	struct sockaddr_in myend;
	int ret;
	int val;
	int proc_nr = 0, proc_free_nr = 0;
	struct msgbuf_st msgbuf_r, msgbuf_s;
	long myid = 1;
	int msgid;
	struct sigaction child_act;

	child_act.sa_handler = SIG_IGN;
	sigemptyset(&child_act.sa_mask);
	child_act.sa_flags = SA_NOCLDWAIT;
	sigaction(SIGCHLD, &child_act, NULL);

	msgid = msgget(IPC_PRIVATE, 0600);
	if (msgid == -1) {
		perror("msgget()");
		goto msgget_err;
	}

	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == -1) {
		perror("socket()");
		goto socket_err;
	}

	val = 1;
	setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

	myend.sin_family = AF_INET;
	myend.sin_port = htons(8899);
	//inet_pton(AF_INET, "172.16.30.83", &myend.sin_addr);
	inet_pton(AF_INET, "127.0.0.1", &myend.sin_addr);
	ret = bind(sd, (struct sockaddr *)&myend, sizeof(myend));
	if (ret == -1) {
		perror("bind()");
		goto bind_err;
	}

	listen(sd, 20);

	msgbuf_s.src = 1;
	while (1) {
		remain_proc(sd, msgid, &proc_nr, &proc_free_nr);
		printf("\033[31mtotal: %d, free: %d\033[0m\n", proc_nr, proc_free_nr);
		msgrcv(msgid, &msgbuf_r, sizeof(long) * 2, myid, 0);
		switch (msgbuf_r.status) {
		case ST_FREE:
			printf("%ld free\n", msgbuf_r.src);
			msgbuf_s.dest = msgbuf_r.src;
			if (proc_free_nr >= PROC_FREE_MAX) {
				msgbuf_s.status = ST_QUIT;
				proc_nr--;
			} else {
				msgbuf_s.status = ST_NOTHING;
				proc_free_nr++;
			}
			msgsnd(msgid, &msgbuf_s, sizeof(long) * 2, 0);
			break;
		case ST_BUSY:
			printf("%ld busy\n", msgbuf_r.src);
			proc_free_nr--;
			break;
		case ST_QUIT:
			printf("%ld quit\n", msgbuf_r.src);
			proc_nr--;
			break;
		}
	}

	close(sd);
	msgctl(msgid, IPC_RMID, NULL);

	return 0;

bind_err:
	close(sd);
socket_err:
	msgctl(msgid, IPC_RMID, NULL);
msgget_err:
	return 1;
}
