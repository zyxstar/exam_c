#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMESIZE 32

struct score {
	int id;
	char name[NAMESIZE];
	int ch;
	int math;
};

static int insert(struct score **box, int *nr, struct score *data)
{
	struct score *tmp;

	tmp = malloc(sizeof(struct score) * (*nr + 1));
	if (tmp == NULL) {
		return -1;
	}
	memcpy(tmp, *box, sizeof(struct score) * *nr);
	tmp[*nr] = *data;
	(*nr)++;

	free(*box);
	*box = tmp;
	return 0;
}

static void travel(struct score *box, int nr)
{
	int i;

	for (i = 0; i < nr; i++) {
		printf("%d %s %d %d\n", box[i].id, box[i].name, box[i].ch, box[i].math);
	}
}

int main(void)
{
	struct score *box = NULL;
	int nr = 0;
	struct score tmp;
	int i;

	for (i = 0; i < 9; i++) {
		tmp.id = i;
		snprintf(tmp.name, NAMESIZE, "stu%d", i);
		tmp.ch = 100 - i;
		tmp.math = 100 - 2 * i;

		insert(&box, &nr, &tmp);
	}

	travel(box, nr);

	return 0;
}
