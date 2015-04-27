#include <stdio.h>

#include "queue.h"

#define NAMESIZE 32

struct score {
	int id;
	char name[NAMESIZE];
	int ch;
};

int main(void)
{
	QUEUE *queue;
	struct score tmp;
	int i;
	int ret;

	queue = queue_creat(sizeof(struct score));
	/* if error */

	for (i = 0; i < 9; i++) {
		tmp.id = i;
		snprintf(tmp.name, NAMESIZE, "stu%d", i);
		tmp.ch = 100 - i;

		queue_enq(queue, &tmp);
		/* if error */
	}

	while (1) {
		ret = queue_deq(queue, &tmp);
		if (ret == -1) {
			break;
		}

		printf("%d, %s, %d\n", tmp.id, tmp.name, tmp.ch);
	}

	queue_destroy(queue);

	return 0;
}
