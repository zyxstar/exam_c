#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "comm.h"
#include "debug.h"

#define BUFSIZE  64

#ifdef DEBUG
#define PROC_NR_MAX        6
#define PROC_FREE_NR_MIN   2
#define PROC_FREE_NR_MAX   5
#define PROC_NR_PER_FORK   3
#define TIMES_MAX          2
#else
#define PROC_NR_MAX        100
#define PROC_FREE_NR_MIN   10
#define PROC_FREE_NR_MAX   60
#define PROC_NR_PER_FORK   20
#define TIMES_MAX          100
#endif

enum child_status {ST_QUIT, ST_FREE, ST_BUSY};

struct msgbuf_st {
	long dest;
	long src;
	enum child_status status;
};

static int min(int a, int b)
{
	return a < b ? a : b;
}

static void jobs(int sd, int msgid)
{
	int newsd;
	struct sockaddr_in hisend;
	socklen_t hislen;
	char buf[BUFSIZE];
	time_t cur;
	struct tm *cur_tm;
	int ret;
	struct msgbuf_st msgbuf;
	int times = 0;

	while (1) {
		hislen = sizeof(hisend); /* must init */
		newsd = accept(sd, (struct sockaddr *)&hisend, &hislen);
		/* if error */
		times++;
		debug("%d busy, times = %d\n", getpid(), times);

		msgbuf.dest = 1;
		msgbuf.src = getpid();
		msgbuf.status = ST_BUSY;
		msgsnd(msgid, &msgbuf, sizeof(long) + sizeof(enum child_status), 0);
		/* if error */

		while (1) {
			ret = read(newsd, buf, BUFSIZE);
			if (ret == -1) {
				if (errno == EINTR) {
					continue;
				}
				perror("read(newsd)");
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
			debug("%d quit, times = %d\n", getpid(), times);
			msgbuf.dest = 1;
			msgbuf.src = getpid();
			msgbuf.status = ST_QUIT;
			msgsnd(msgid, &msgbuf, sizeof(long) + sizeof(enum child_status), 0);
			/* if error */
			break;
		}

		debug("%d free, times = %d\n", getpid(), times);
		msgbuf.dest = 1;
		msgbuf.src = getpid();
		msgbuf.status = ST_FREE;
		msgsnd(msgid, &msgbuf, sizeof(long) + sizeof(enum child_status), 0);
		/* if error */
		debug("%d recv free, times = %d\n", getpid(), times);

		msgrcv(msgid, &msgbuf, sizeof(long) + sizeof(enum child_status), getpid(), 0);
		if (msgbuf.status == ST_QUIT) {
			debug("%d recv quit, times = %d\n", getpid(), times);
			break;
		}
	}
}

static int proc_remain(int sd, int msgid, int *proc_nr, int *proc_free_nr)
{
	int num;
	int i;
	pid_t pid;

	debug("call proc_remain, proc_nr = %d, proc_free_nr = %d\n", *proc_nr, *proc_free_nr);

	if (*proc_free_nr >= PROC_FREE_NR_MIN) {
		debug("proc_remain return, proc_nr = %d, proc_free_nr = %d\n", *proc_nr, *proc_free_nr);
		return 0;
	}

	num = min(PROC_NR_PER_FORK, PROC_NR_MAX - *proc_nr);
	for (i = 0; i < num; i++) {
		pid = fork();
		if (pid == -1) {
			break;
		}
		if (pid == 0) {
			jobs(sd, msgid);
			exit(0);
		}
	}

	*proc_nr += i;
	*proc_free_nr += i;
	debug("proc_remain return, proc_nr = %d, proc_free_nr = %d\n", *proc_nr, *proc_free_nr);
	return i;
}

int main(void)
{
	int sd;
	int msgid;
	int ret;
	struct sockaddr_in myend;
	struct sigaction act;
	int proc_nr, proc_free_nr;
	struct msgbuf_st msgbuf;

	act.sa_handler = SIG_IGN;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_NOCLDWAIT;
	sigaction(SIGCHLD, &act, NULL);

	msgid = msgget(IPC_PRIVATE, 0600);
	/* if error */

	sd = socket(AF_INET, SOCK_STREAM, 0);
	/* if error */

	myend.sin_family = AF_INET;
	myend.sin_port = SERVER_PORT;
	inet_pton(AF_INET, SERVER_IP, &myend.sin_addr);
	ret = bind(sd, (struct sockaddr *)&myend, sizeof(myend));
	if (ret == -1) {
		perror("bind()");
		close(sd);
		return 1;
	}

	listen(sd, 20);

	//jobs(sd, msgid);
	proc_nr = 0, proc_free_nr = 0;
	proc_remain(sd, msgid, &proc_nr, &proc_free_nr);

	while (1) {
		debug("main: proc_nr = %d, proc_free_nr = %d\n", proc_nr, proc_free_nr);
		msgrcv(msgid, &msgbuf, sizeof(long) + sizeof(enum child_status), 1, 0);
		/* if error */
		switch (msgbuf.status) {
		case ST_QUIT:
			debug("main: %d quit\n", msgbuf.src);
			proc_nr--;
			proc_remain(sd, msgid, &proc_nr, &proc_free_nr);
			break;
		case ST_FREE:
			debug("main: %d free\n", msgbuf.src);
			msgbuf.dest = msgbuf.src;
			msgbuf.src = 1;
			if (proc_free_nr >= PROC_FREE_NR_MAX) {
				msgbuf.status = ST_QUIT;
				debug("main: send quit to %d\n", msgbuf.dest);
				proc_nr--;
			} else {
				msgbuf.status = ST_FREE;
				debug("main: send free to %d\n", msgbuf.dest);
				proc_free_nr++;
			}
			msgsnd(msgid, &msgbuf, sizeof(long) + sizeof(enum child_status), 0);
			break;
		case ST_BUSY:
			debug("main: %d busy\n", msgbuf.src);
			proc_free_nr--;
			proc_remain(sd, msgid, &proc_nr, &proc_free_nr);
			break;
		}
	}

	/* destroy msgid */

	close(sd);

	return 0;
}
