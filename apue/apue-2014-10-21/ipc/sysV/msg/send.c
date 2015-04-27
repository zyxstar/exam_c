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

	msgid = msgget(key, 0);
	if (msgid == -1) {
		perror("msgget()");
		return 1;
	}
	printf("key: 0x%x, msgid: %d\n", key, msgid);

	msgbuf.dest = 25;
	while (1) {
		ret = read(0, msgbuf.text, TEXT_SIZE);
		/* if error */
		if (ret == 0) {
			break;
		}

		msgsnd(msgid, &msgbuf, ret, 0);
		/* if error */
	}

	return 0;
}
