#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "comm.h"

#define IDBUFSIZE 32

/* $ ./a.out id */
int main(int argc, char **argv)
{
	int msgid;
	struct msgbuf buf, sndbuf;
	int ret;
	long myid;
	FILE *fp;
	char idbuf[IDBUFSIZE];

	if (argc != 2) {
		fprintf(stderr, "argment...\n");
		return 1;
	}

	myid = atol(argv[1]);

	fp = fopen("private", "r");
	/* if error */
	fgets(idbuf, IDBUFSIZE, fp);
	msgid = atoi(idbuf);
	fclose(fp);

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
