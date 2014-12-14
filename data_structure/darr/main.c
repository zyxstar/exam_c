#include <stdio.h>
#include <string.h>

#include "darr.h"

#define NAMESIZE 25

struct stuinfo {
	int id;
	char name[NAMESIZE];
	int score;
};

static void print_s(const void *data)
{
	const struct stuinfo *datap = data;

	printf("%d %s %d\n", 
			datap->id,
			datap->name,
			datap->score);
}

static int id_cmp(const void *data, const void *key)
{
	const struct stuinfo *datap = data;
	const int *keyp = key;

	return (*keyp - datap->id);
}

static int name_cmp(const void *data, const void *key)
{
	const struct stuinfo *datap = data;
	const char *keyp = key;

	return strcmp(keyp, datap->name);
}

int main(void)
{
	int i;
	int id = 3;
	char *name = "stu4";
	struct stuinfo tmp;
	struct stuinfo *stup;
	DARR head = NULL;

	head = darr_create(sizeof(struct stuinfo));
	if(NULL == head)
	{
		return -1;
	}

	for(i = 0; i < 6; i++)
	{
		tmp.id = i;
		snprintf(tmp.name,NAMESIZE,"stu%d", i);
		tmp.score = 100;

		darr_insert(head, &tmp);
	}
#if 0
	stup = darr_find(head, name, name_cmp);
	//stup = darr_find(head, &id, id_cmp);
	if(stup == NULL)
		printf("not found\n");
	else
		print_s(stup);
#endif
	darr_delete(head, &id, id_cmp);
	darr_delete(head, name, name_cmp);

	darr_display(head, print_s);
	darr_dispose(head);
	
	return 0;
}
