#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 128

#ifdef DEBUG
#define PROC_PER_FORK  3
#define PROC_FREE_MIN  2
#define PROC_FREE_MAX  6
#define PROC_MAX       8
#define TIMES_MAX      2
#else
#define PROC_PER_FORK  20
#define PROC_FREE_MIN  10
#define PROC_FREE_MAX  100
#define PROC_MAX       1000
#define TIMES_MAX      1000
#endif	/* DEBUG */

#define PARENT_ID      1

enum {ST_QUIT, ST_FREE, ST_BUSY, ST_NOTHING};

struct msgbuf_st {
	long dest;
	long src;
	long status;
};

#define MSG_BUFSIZE (sizeof(long) * 2)

static void job(int msgid, int sd)
{
	char buf[BUFSIZE];
	int ret;
	int newsd;
	struct sockaddr_in hisend;
	socklen_t hislen;
	int times = 0;
	struct msgbuf_st msgbuf_r, msgbuf_s;

	hislen = sizeof(hisend);
	while (1) {
		newsd = accept(sd, (struct sockaddr *)&hisend, &hislen);
		times++;
		msgbuf_s.dest = PARENT_ID;
		msgbuf_s.src = getpid();
		msgbuf_s.status = ST_BUSY;
		msgsnd(msgid, &msgbuf_s, MSG_BUFSIZE, 0);

		while (1) {
			ret = read(newsd, buf, BUFSIZE);
			if (ret == 0) {
				break;
			}

			write(1, buf, ret);

			/* fix me */
			write(newsd, "qnmlgb\n", 7);
		}
		close(newsd);

		if (times >= TIMES_MAX) {
			msgbuf_s.dest = PARENT_ID;
			msgbuf_s.src = getpid();
			msgbuf_s.status = ST_QUIT;
			msgsnd(msgid, &msgbuf_s, MSG_BUFSIZE, 0);
			break;
		} else {
			msgbuf_s.dest = PARENT_ID;
			msgbuf_s.src = getpid();
			msgbuf_s.status = ST_FREE;
			msgsnd(msgid, &msgbuf_s, MSG_BUFSIZE, 0);

			msgrcv(msgid, &msgbuf_r, MSG_BUFSIZE, getpid(), 0);
			if (msgbuf_r.status == ST_QUIT) {
				break;
			}
		}
	}
}

static void fork_job(int msgid, int sd, int *proc_nr, int *proc_free_nr)
{
	int i;
	pid_t pid;

	if (*proc_free_nr >= PROC_FREE_MIN) {
		return;
	}

	for (i = 0; (i < PROC_PER_FORK) && (*proc_nr < PROC_MAX); i++) {
		pid = fork();
		/* if error */
		if (pid == 0) {
			job(msgid, sd);
			close(sd);
			exit(0);
		}
		*proc_nr += 1;
		*proc_free_nr += 1;
	}
}

int main(void)
{
	int sd;
	struct sockaddr_in myend;
	int ret;
	struct sigaction act;
	int proc_nr = 0, proc_free_nr = 0;
	int msgid;
	struct msgbuf_st msgbuf_r, msgbuf_s;

	act.sa_handler = SIG_DFL;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_NOCLDWAIT;
	sigaction(SIGCHLD, &act, NULL);

	msgid = msgget(IPC_PRIVATE, 0600);
	/* if error */

	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == -1) {
		perror("socket()");
		return 1;
	}

	myend.sin_family = AF_INET;
	myend.sin_port = htons(8899);
	inet_pton(AF_INET, "192.168.100.93", &myend.sin_addr);
	bind(sd, (struct sockaddr *)&myend, sizeof(myend));
	/* if error */

	listen(sd, 20);
	/* if error */

	fork_job(msgid, sd, &proc_nr, &proc_free_nr);
	while (1) {
		printf("before msgrcv(), proc_nr = %d, proc_free_nr = %d\n", proc_nr, proc_free_nr);
		msgrcv(msgid, &msgbuf_r, MSG_BUFSIZE, PARENT_ID, 0);
		switch (msgbuf_r.status) {
		case ST_FREE:
			if (proc_free_nr == PROC_FREE_MAX) {
				msgbuf_s.src = PARENT_ID;
				msgbuf_s.dest = msgbuf_r.src;
				msgbuf_s.status = ST_QUIT;
				msgsnd(msgid, &msgbuf_s, MSG_BUFSIZE, 0);
				proc_nr--;
			} else {
				msgbuf_s.src = PARENT_ID;
				msgbuf_s.dest = msgbuf_r.src;
				msgbuf_s.status = ST_NOTHING;
				msgsnd(msgid, &msgbuf_s, MSG_BUFSIZE, 0);
				proc_free_nr++;
			}
			break;
		case ST_BUSY:
			proc_free_nr--;
			break;
		case ST_QUIT:
			proc_nr--;
			break;
		}
		printf("after msgrcv(), proc_nr = %d, proc_free_nr = %d\n", proc_nr, proc_free_nr);
		fork_job(msgid, sd, &proc_nr, &proc_free_nr);
		printf("after fork_job(), proc_nr = %d, proc_free_nr = %d\n", proc_nr, proc_free_nr);
	}

	close(sd);

	return 0;
}
