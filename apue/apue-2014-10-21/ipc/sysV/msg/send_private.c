#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <stdio.h>

#include "comm.h"

int main(void)
{
	int msgid;
	int ret;
	struct msgbuf_st msgbuf;
	FILE *fp;
	char idbuf[128];

	fp = fopen("./priv_id", "r");
	fgets(idbuf, 128, fp);
	msgid = atoi(idbuf);
	printf("msgid: %d\n", msgid);

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
