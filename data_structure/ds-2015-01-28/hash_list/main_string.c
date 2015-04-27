#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "llist.h"

#define LIST_NR    127
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

static unsigned int hash(const char *str)
{
	unsigned int sum = 0;

	while (*str != '\0') {
		sum = (sum << 5) ^ *str;
		str++;
	}

	return sum;
}

int insert(const struct score *data)
{
	int ind;
	ind = hash(data->name) % LIST_NR;
	llist_insert(list[ind], data, DIR_BACK);

	return 0;
}

static int name_cmp(const void *key, const void *data)
{
	const char *k = key;
	const struct score *d = data;

	return strcmp(k, d->name);
}

struct score *search(const char *name)
{
	int ind;
        ind = hash(name) % LIST_NR;

	return llist_search(list[ind], name, name_cmp);
}

static int getnum(LLIST *l)
{
	struct llist_node_st *cur;
	int sum;

	sum = 0;
	for (cur = l->head.next; cur != &l->head; cur = cur->next) {
		sum++;
	}

	return sum;
}

void travel(void)
{
	int i;

	for (i = 0; i < LIST_NR; i++) {
		printf("%d ", getnum(list[i]));
	}
	printf("\n");
}

static void rand_name(char *name, int size)
{
	int i;
	int len;

	len = (unsigned)rand() % (size - 5) + 4;
	for (i = 0; i < len; i++) {
		name[i] = (unsigned)rand() % 26 + 'a';
	}
	name[i] = '\0';
}

int main(void)
{
	struct score tmp, *data;
	int i;

	srand(getpid());

	init();

	for (i = 0; i < 1024 * 1024; i++) {
		tmp.id = i;
		tmp.ch = 100 - i;
		//snprintf(tmp.name, NAMESIZE, "stu%d", i);
		rand_name(tmp.name, NAMESIZE);

		insert(&tmp);
	}

	//data = search("stu6");
	//printf("%d %s %d\n", data->id, data->name, data->ch);

	travel();

	return 0;
}
