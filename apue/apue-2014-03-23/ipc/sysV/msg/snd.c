#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "comm.h"

/* $ ./a.out id */
int main(int argc, char **argv)
{
	int msgid;
	key_t key;
	struct msgbuf buf, sndbuf;
	int ret;
	long myid;

	if (argc != 2) {
		fprintf(stderr, "argment...\n");
		return 1;
	}

	myid = atol(argv[1]);

	key = ftok(PATHNAME, PROJ_ID);
	if (key == -1) {
		perror("ftok()");
		return 1;
	}

	msgid = msgget(key, 0);
	if (msgid == -1) {
		perror("msgget()");
		return 1;
	}

	printf("key = %x, msgid = %d\n", key, msgid);


	sndbuf.src = myid;
	sndbuf.dest = 5;
	fgets(sndbuf.data, DATASIZE, stdin);
	msgsnd(msgid, &sndbuf, sizeof(long) + strlen(sndbuf.data) + 1, 0);
	/* if error */

	ret = msgrcv(msgid, &buf, MSGBUFSIZE, myid, 0);
	/* if error */
	printf("from %d: %s\n", buf.src, buf.data);

	return 0;
}
