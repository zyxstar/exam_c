#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "llist.h"

#define LIST_NR    10
#define NAMESIZE   32

struct score {
	int id;
	char name[NAMESIZE];
	int ch;
};

static LLIST *list[LIST_NR];

int init(void)
{
	int i;

	for (i = 0; i < LIST_NR; i++) {
		list[i] = llist_creat(sizeof(struct score));
		/* if error */
	}
}

static int hash(int id)
{
	return id;
}

int insert(const struct score *data)
{
	int ind;
	ind = hash(data->id) % LIST_NR;
	llist_insert(list[ind], data, DIR_BACK);

	return 0;
}

static int id_cmp(const void *key, const void *data)
{
	const int *k = key;
	const struct score *d = data;

	return *k - d->id;
}

struct score *search(int id)
{
	int ind;
        ind = hash(id) % LIST_NR;

	return llist_search(list[ind], &id, id_cmp);
}

int main(void)
{
	struct score tmp, *data;
	int i;

	init();

	for (i = 0; i < 100; i++) {
		tmp.id = i;
		tmp.ch = 100 - i;
		snprintf(tmp.name, NAMESIZE, "stu%d", i);

		insert(&tmp);
	}

	data = search(25);
	printf("%d %s %d\n", data->id, data->name, data->ch);

	return 0;
}
