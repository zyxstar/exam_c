#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <stdio.h>

#include "comm.h"

int main(void)
{
	int msgid;
	key_t key;
	int ret;
	struct msgbuf_st msgbuf;

	key = ftok(PATH, PROJ_ID);
	if (key == -1) {
		perror("ftok()");
		return 1;
	}

	msgid = msgget(key, IPC_CREAT | 0666);
	if (msgid == -1) {
		perror("msgget()");
		return 1;
	}
	printf("key: 0x%x, msgid: %d\n", key, msgid);

	while (1) {
		ret = msgrcv(msgid, &msgbuf, TEXT_SIZE, 5, 0);
		/* if error */

		write(1, msgbuf.text, ret);
	}

	return 0;
}
