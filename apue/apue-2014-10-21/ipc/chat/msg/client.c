#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "comm.h"

#define BUFSIZE (sizeof(long) * 8)

static void read_stdin(int msgid, long myid)
{
	char buf[BUFSIZE];
	struct msgbuf_st mbuf;
	int len;
	char *retp;

	mbuf.src = myid;
	while (1) {
		retp = fgets(buf, BUFSIZE, stdin);
		if (retp == NULL) {
			break;
		}
		mbuf.dest = atol(buf);

		fgets(mbuf.text, TEXT_SIZE, stdin);
		len = strlen(mbuf.text);

		msgsnd(msgid, &mbuf, len + 1 + sizeof(long), 0);
	}
}

static void read_msg(int msgid, long myid)
{
	struct msgbuf_st mbuf;
	int ret;

	while (1) {
		ret = msgrcv(msgid, &mbuf, sizeof(long) + TEXT_SIZE, myid, 0);
		/* if error */
		printf("\033[31m%ld:%s\033[0m", mbuf.src, mbuf.text);
		fflush(stdout);
	}
}

/* $ ./a.out myid */
int main(int argc, char **argv)
{
	key_t key;
	int msgid;
	pid_t pid;
	long myid;

	if (argc != 2) {
		fprintf(stderr, "argment...\n");
		exit(1);
	}

	myid = atol(argv[1]);

	key = ftok(PATH, PROJ_ID);
	msgid = msgget(key, IPC_CREAT | 0666);
	/* if error */

	pid = fork();
	/* if error */
	if (pid == 0) {
		read_stdin(msgid, myid);
		exit(0);
	}
	read_msg(msgid, myid);

	return 0;
}
