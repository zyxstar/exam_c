#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEXTSIZE 128
#define RECVSIZE (TEXTSIZE + sizeof(long))
#define BUFSIZE  TEXTSIZE

struct msgbuf_st {
	long dest_id;
	long src_id;
	char text[TEXTSIZE];
};

static void send2msq(int msgid, long myid)
{
	struct msgbuf_st msgbuf;
	char buf[BUFSIZE];

	msgbuf.src_id = myid;
	while (1) {
		fgets(buf, BUFSIZE, stdin);
		sscanf(buf, "%ld:%s", &msgbuf.dest_id, msgbuf.text);

		msgsnd(msgid, &msgbuf, sizeof(long) + strlen(msgbuf.text) + 1, 0);
	}
}

/* ./a.out myid */
int main(int argc, char **argv)
{
	int msgid;
	key_t key;
	long myid;
	struct msgbuf_st msgbuf;
	pid_t pid;
	int ret;

	if (argc != 2) {
		fprintf(stderr, "argment...\n");
		return 1;
	}

	myid = atol(argv[1]);

	key = ftok("/etc/shadow", 'C');
	/* if error */

	msgid = msgget(key, IPC_CREAT | 0600);
	/* if error */

	pid = fork();
	/* if error */
	if (pid == 0) {
		send2msq(msgid, myid);

		return 0;
	}

	while (1) {
		ret = msgrcv(msgid, &msgbuf, RECVSIZE, myid, 0);
		printf("from %ld: %s\n", msgbuf.src_id, msgbuf.text);
	}

	return 0;
}
