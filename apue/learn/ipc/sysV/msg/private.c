#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#include <stdio.h>

#define TEXTSIZE 128

struct msgbuf_st {
	long type;
	char text[TEXTSIZE];
};

int main(void)
{
	int msgid;
	struct msgbuf_st msgbuf;
	int ret;
	pid_t pid;

	msgid = msgget(IPC_PRIVATE, 0666);
	if (msgid == -1) {
		perror("msgget()");
		return 1;
	}
	//printf("id: %d, key: %x\n", msgid, IPC_PRIVATE);

	pid = fork();
	/* if error */
	if (pid == 0) {
		msgbuf.type = 100;
		ret = snprintf(msgbuf.text, TEXTSIZE, "qnmlgb\n");
		msgsnd(msgid, &msgbuf, ret + 1, 0);
		return 0;
	}

	msgrcv(msgid, &msgbuf, TEXTSIZE, 0, 0);
	printf("%s", msgbuf.text);

	wait(NULL);

	msgctl(msgid, IPC_RMID, NULL);

	return 0;
}
