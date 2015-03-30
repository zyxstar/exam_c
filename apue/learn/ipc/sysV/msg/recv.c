#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <stdio.h>

#define TEXTSIZE 128

struct msgbuf_st {
	long type;
	char text[TEXTSIZE];
};

/* ./a.out type */
int main(int argc, char **argv)
{
	int msgid;
	key_t key;
	struct msgbuf_st msgbuf;
	int ret;
	long type;

	if (argc != 2) {
		fprintf(stderr, "argment...\n");
		return 1;
	}

	type = atol(argv[1]);

	key = ftok("/etc/passwd", 'M');
	if (key == -1) {
		perror("ftok()");
		return 1;
	}

	msgid = msgget(key, IPC_CREAT | 0666);
	if (msgid == -1) {
		perror("msgget()");
		return 1;
	}

	printf("type: %ld, key: %x, msgid: %d\n", type, key, msgid);

	while (1) {
		ret = msgrcv(msgid, &msgbuf, TEXTSIZE, type, 0);
		/* if error */
		write(1, msgbuf.text, ret);
	}

	msgctl(msgid, IPC_RMID, NULL);

	return 0;
}
