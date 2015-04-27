#include <stdio.h>
#include <stdlib.h>

struct score {
	int id;
	int ch;
	int math;
};

struct node {
	struct score data;
	struct node *next;
};

int insert(struct node **list, struct score *data)
{
	struct node *new;

	new = malloc(sizeof(*new));
	if (new == NULL) {
		return -1;
	}

	new->data = *data;
	(*new).data = *data;

	new->next = *list;
	*list = new;

	return 0;
}

void travel(struct node *list)
{
	struct node *cur;

	for (cur = list; cur != NULL; cur = cur->next) {
		printf("%d: %d %d\n", cur->data.id, cur->data.ch, cur->data.math);
	}
}

struct score *find(struct node *list, int id)
{
	struct node *cur;

	for (cur = list; cur != NULL; cur = cur->next) {
		if (cur->data.id == id) {
			return &cur->data;
		}
	}
	return NULL;
}

void delete(struct node **list, int id)
{
#if 1
	struct node **cur, *node;

	for (cur = list; *cur != NULL; cur = &(*cur)->next) {
		if ((*cur)->data.id == id) {
			node = *cur;
			*cur = node->next;
			free(node);
			return;
		}
	}
#else
	struct node *cur, *pre;
	cur = *list;
	if (cur->data.id == id) {
		*list = cur->next;
		free(cur);
		return;
	}
	for (pre = cur; cur != NULL; pre= cur, cur = cur->next) {
		if (cur->data.id == id) {
			pre->next = cur->next;
			free(cur);
			return;
		}
	}
#endif
}

void destroy(struct node *list)
{
	struct node *node, *next;

	for (node = list; node != NULL; node = next) {
		next = node->next;
		free(node);
	}
}

int main(void)
{
	struct node *list = NULL;
	struct score tmp, *data;
	int i;

	for (i = 0; i < 5; i++) {
		tmp.id = i;
		tmp.ch = 100 - i;
		tmp.math = 100 - 2 * i;

		insert(&list, &tmp);
	}

	travel(list);

	printf("\n");
#if 0
	data = find(list, 10);
	if (data == NULL) {
		printf("Can not find.\n");
	} else {
		printf("%d: %d %d\n", data->id, data->ch, data->math);
	}
#else
        delete(&list, 0);
	travel(list);
#endif
	destroy(list);

	return 0;
}
