#include <stdio.h>
#include <stdlib.h>

struct node_st {
	int data;
	struct node_st *next;
};

static int insert(struct node_st **list, int data)
{
	struct node_st *newnode;

	newnode = malloc(sizeof(*newnode));
	if (newnode == NULL) {
		return -1;
	}

	newnode->data = data;
	newnode->next = *list;
	*list = newnode;

	return 0;
}

static void travel(struct node_st *list)
{
	struct node_st *cur;

	for (cur = list; cur != NULL; cur = cur->next) {
		printf("%d ", cur->data);
	}
	printf("\n");
}

void travel_tmp(struct node_st *list)
{
	for (; list != NULL; list = list->next) {
		printf("%d ", list->data);
	}
	printf("\n");
}

static void delete(struct node_st **list, int data)
{
	struct node_st *prev, *cur;

	cur = *list;
	if (cur == NULL) {
		return;
	}
	if (cur->data == data) {
		*list = cur->next;
		free(cur);
		return;
	}

	prev = cur;
	cur = cur->next;
	for (; cur != NULL; cur = cur->next) {
		if (cur->data == data) {
			prev->next = cur->next;
			free(cur);
			return;
		}
		prev = cur;
	}
}

static void destroy(struct node_st *list)
{
	struct node_st *cur, *next;

	for (cur = list; cur != NULL; cur = next) {
		next = cur->next;
		free(cur);
	}
}

int main(void)
{
	int arr[] = {3,2,1,6,7};
	int i;
	struct node_st *list = NULL;

	for (i = 0; i < sizeof(arr) / sizeof(*arr); i++) {
		insert(&list, arr[i]);
	}

	travel(list);
	delete(&list, 7);
	travel(list);

	destroy(list);

	return 0;
}
