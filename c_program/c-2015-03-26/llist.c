#include <stdio.h>
#include <stdlib.h>

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
	struct node_st *newnode;

	newnode = malloc(sizeof(*newnode));
	if (newnode == NULL) {
		return -1;
	}

	newnode->data = *data;
	newnode->next = *list;
	*list = newnode;

	return 0;
}

void travel(struct node_st *list)
{
	struct node_st *cur;

	for (cur = list; cur != NULL; cur = cur->next) {
		printf("%d, %s, %d, %d\n", cur->data.id, cur->data.name, cur->data.ch, cur->data.math);
	}
}

void destroy(struct node_st *list)
{
	struct node_st *cur, *next;

	for (cur = list; cur != NULL; cur = next) {
		next = cur->next;
		free(cur);
	}
}

void delete(struct node_st **list, int id)
{
	struct node_st *cur, *prev = NULL;

	cur = *list;
	if (cur->data.id == id) {
		*list = cur->next;
		free(cur);
		return;
	}

	prev = cur;
	for (cur = cur->next; cur != NULL; cur = cur->next) {
		if (cur->data.id == id) {
			prev->next = cur->next;
			free(cur);
			return;
		}
		prev = cur;
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

int fetch(struct node_st **list, int id, struct score *data)
{
	struct node_st *cur, *prev = NULL;

	cur = *list;
	if (cur->data.id == id) {
		*data = cur->data;
		*list = cur->next;
		free(cur);
		return 0;
	}

	prev = cur;
	for (cur = cur->next; cur != NULL; cur = cur->next) {
		if (cur->data.id == id) {
			*data = cur->data;
			prev->next = cur->next;
			free(cur);
			return 0;
		}
		prev = cur;
	}

	return -1;
}

int main(void)
{
	struct node_st *list = NULL;
	struct score tmp, *datap;
	int i;
	int ret;

	for (i = 0; i < 9; i++) {
		tmp.id = i;
		snprintf(tmp.name, NAMESIZE, "stu%d", i);
		tmp.ch = 100 - i;
		tmp.math = 100 - 2 * i;

		insert(&list, &tmp);
	}

	travel(list);
	ret = fetch(&list, 0, &tmp);
	if (ret == 0) {
		printf("fetch: %d %s %d %d\n", tmp.id, tmp.name, tmp.ch, tmp.math);
	} else {
		printf("Can not find.\n");
	}
	travel(list);

#if 0
	delete(&list, 8);
	datap = find(list, 0);
	if (datap == NULL) {
		printf("Can not find.\n");
	} else {
		printf("%d %s %d %d\n", datap->id, datap->name, datap->ch, datap->math);
	}
#endif

	destroy(list);
	return 0;
}
