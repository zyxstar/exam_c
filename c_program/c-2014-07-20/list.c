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

struct node_st {
	struct score data;
	struct node_st *next;
};

int insert(struct node_st **list, struct score *data)
{
	struct node_st *new;

	new = malloc(sizeof(*new));
	if (new == NULL) {
		return -1;
	}

	new->data = *data;

	new->next = *list;
	*list = new;

	return 0;
}

void travel(struct node_st *list)
{
	struct node_st *cur;

	for (cur = list; cur != NULL; cur = cur->next) {
		printf("%d %s %d %d\n", cur->data.id, cur->data.name, cur->data.ch, cur->data.math);
	}
}

struct score *find(struct node_st *list, int id)
{
	struct node_st *cur;

	for (cur = list; cur != NULL; cur = cur->next) {
		if (cur->data.id == id) {
			return &cur->data;
		}
	}
	return NULL;
}

int main(void)
{
	struct node_st *list = NULL;
	struct score tmp, *datap;
	int i;

	for (i = 0; i < 5; i++) {
		tmp.id = i;
		tmp.ch = 100 - i;
		tmp.math = 100 - 2 * i;
		snprintf(tmp.name, NAMESIZE, "stu%d", i);

		insert(&list, &tmp);
		/* if error */
	}

	travel(list);
	printf("\n");

	datap = find(list, 40);
	if (datap == NULL) {
		printf("Can not find.\n");
	} else {
		printf("%d %s %d %d\n", datap->id, datap->name, datap->ch, datap->math);
	}

	//destroy(list);

	return 0;
}
