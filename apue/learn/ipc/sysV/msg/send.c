#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <stdio.h>
#include <string.h>

#define TEXTSIZE 128
#define BUFSIZE  (TEXTSIZE)

struct msgbuf_st {
	long type;
	char text[TEXTSIZE];
};

/* input msg like    5:text */
int main(void)
{
	int msgid;
	key_t key;
	struct msgbuf_st msgbuf;
	int ret;
	char buf[BUFSIZE];

	key = ftok("/etc/passwd", 'M');
	if (key == -1) {
		perror("ftok()");
		return 1;
	}

	msgid = msgget(key, 0);
	if (msgid == -1) {
		perror("msgget()");
		return 1;
	}

	while (1) {
		fgets(buf, BUFSIZE, stdin);
		/* if error */
		sscanf(buf, "%ld:%s", &msgbuf.type, msgbuf.text);
		msgbuf.text[strlen(msgbuf.text) + 1] = '\0';
		msgbuf.text[strlen(msgbuf.text) - 1] = '\n';
		printf("will send, type: %ld, text: %s", msgbuf.type, msgbuf.text);

		ret = msgsnd(msgid, &msgbuf, strlen(msgbuf.text), 0);
		/* if error */
	}

	return 0;
}
