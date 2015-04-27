#include <stdio.h>
#include <string.h>

#include "llist.h"

#define NAMESIZE    32
#define LIST_NR     1027
#define DATA_NR     204800

struct score {
	int id;
	char name[NAMESIZE];
};

static LLIST *list[LIST_NR];

static void print_score(struct score *data)
{
	printf("%d %s\n", data->id, data->name);
}

static int id_cmp(const void *id, const void *data)
{
	const int *key = id;
	const struct score *d = data;
	return *key - d->id;
}

static int name_cmp(const void *name, const void *data)
{
	const struct score *d = data;
	return strcmp(name, d->name);
}

static unsigned hash(const char *str)
{
	unsigned int sum = 0;
	int i;

	for (i = 0; str[i] != '\0'; i++) {
		sum = (sum << 5) ^ str[i];
	}
	return sum;
}

int insert(struct score *data)
{
	unsigned int ind;

	ind = hash(data->name) % LIST_NR;
	return llist_insert(list[ind], data);
}

struct score *find(const char *name)
{
	unsigned int ind;

	ind = hash(name) % LIST_NR;
	return llist_find(list[ind], name, name_cmp);
}

static int init(void)
{
	int i;

	for (i = 0; i < LIST_NR; i++) {
		list[i] = llist_creat(sizeof(struct score));
		if (list[i] == NULL) {
			goto err;
		}
	}

	return 0;

	i = LIST_NR;
err:
	for (i--; i >= 0; i--) {
		llist_destroy(list[i]);
	}
	return -1;
}

static void destroy(void)
{
	int i;

	for (i = 0; i < LIST_NR; i++) {
		llist_destroy(list[i]);
	}
}

static void rand_name(char *name)
{
	unsigned int num;
	int i;

	num = (unsigned)rand() % 7 + 3;
	for (i = 0; i < num; i++) {
		name[i] = (unsigned)rand() % 26 + 'a';
	}
	name[i] = '\0';
}

static void travel(void)
{
	int i;
	int num;

	for (i = 0; i < LIST_NR; i++) {
		num = llist_get_num(list[i]);
		printf("%d ", num);
#if 0
		if (i % 30 == 29) {
			printf("\n");
		}
#endif
	}
}

int main(void)
{
	struct score tmp, *datap;
	int i;

	srand(getpid());

	init();

	for (i = 0; i < DATA_NR; i++) {
		tmp.id = i;
		//snprintf(tmp.name, NAMESIZE, "stu%d", i);
		rand_name(tmp.name);

		insert(&tmp);
	}

	travel();

#if 0
	datap = find("xxx");
	if (datap == NULL) {
		printf("Can not find.\n");
	} else {
		print_score(datap);
	}
#endif
	destroy();

	return 0;
}
