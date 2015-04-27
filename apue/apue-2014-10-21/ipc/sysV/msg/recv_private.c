#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>

#include "comm.h"

static int msgid;

static void rmid(int unuse)
{
	msgctl(msgid, IPC_RMID, NULL);
	exit(0);
}

int main(void)
{
	int ret;
	struct msgbuf_st msgbuf;
	FILE *fp;

	signal(SIGINT, rmid);

	msgid = msgget(IPC_PRIVATE, 0666);
	if (msgid == -1) {
		perror("msgget()");
		return 1;
	}
	printf("msgid: %d\n", msgid);

	fp = fopen("./priv_id", "w");
	/* if error */
	fprintf(fp, "%d", msgid);
	fclose(fp);

	while (1) {
		ret = msgrcv(msgid, &msgbuf, TEXT_SIZE, -25, 0);
		/* if error */

		write(1, msgbuf.text, ret);
	}

	return 0;
}
