#include <stdio.h>
#include <string.h>

#include <llist.h>

#define NAMESIZE  32

struct score {
	int id;
	char name[NAMESIZE];
	int ch;
	int math;
};

static void print_score(void *data, void *unuse)
{
	struct score *d = data;

	printf("%d, %s, %d, %d\n", d->id, d->name, d->ch, d->math);
}

int main(void)
{
	struct score tmp, *data;
	int i;
	LLIST *list;
	int ret;

	list = llist_load("tmp");
	if (list == NULL) {
		fprintf(stderr, "load failed.\n");
		return 1;
	}

	llist_travel(list, print_score, NULL);

	llist_destroy(list);
	return 0;
}
