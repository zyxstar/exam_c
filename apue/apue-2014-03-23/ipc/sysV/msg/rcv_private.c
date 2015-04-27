#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "comm.h"

#define CMDSIZE 128

int main(void)
{
	int msgid;
	struct msgbuf buf, sndbuf;
	int ret;
	char cmd[CMDSIZE];

	msgid = msgget(IPC_PRIVATE, IPC_CREAT | 0666);
	if (msgid == -1) {
		perror("msgget()");
		return 1;
	}

	snprintf(cmd, CMDSIZE, "echo %d > private", msgid);
	system(cmd);

	printf("key = %x, msgid = %d\n", IPC_PRIVATE, msgid);

	sndbuf.src = 1;
	while (1) {
		ret = msgrcv(msgid, &buf, MSGBUFSIZE, -5, 0);
		if (ret == -1) {
			if (errno == EINTR) {
				continue;
			}
			perror("msgrcv()");
			break;
		}
		printf("from %d: %s\n", buf.src, buf.data);
		if (strncmp(buf.data, "quit", 4) == 0) {
			break;
		}

		sndbuf.dest = buf.src;
		ret = snprintf(sndbuf.data, DATASIZE, "ACK");
		msgsnd(msgid, &sndbuf, sizeof(long) + ret + 1, 0);
	}

	/* fix me */
	msgctl(msgid, IPC_RMID, NULL);

	return 0;
}
