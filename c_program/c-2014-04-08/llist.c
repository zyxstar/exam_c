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
	struct node *newnode;

	newnode = malloc(sizeof(*newnode));
	if (newnode == NULL) {
		return -1;
	}

	newnode->data = *data;
	newnode->next = *list;
	*list = newnode;

	return 0;
}

void travel(struct node *list)
{
	struct node *cur;

	for (cur = list; cur != NULL; cur = cur->next) {
		printf("%d %d %d\n", cur->data.id, cur->data.ch, cur->data.math);
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
#if 0
	struct node **cur, *save;
	for (cur = list; *cur != NULL; cur = &(*cur)->next) {
		if ((*cur)->data.id == id) {
			save = *cur;
			*cur = save->next;
			free(save);
			return;
		}
	}
#else
	struct node *cur, *prev;
	for (cur = *list; cur != NULL; cur = cur->next) {
		if (cur->data.id == id) {
			if (cur == *list) {
				*list = cur->next;
			} else {
				prev->next = cur->next;
			}
			free(cur);
			return;
		}
		prev = cur;
	}
#endif
}

void destroy(struct node *list)
{
	struct node *cur, *next;

	for (cur = list; cur != NULL; cur = next) {
		next = cur->next;
		free(cur);
	}

}

int main(void)
{
	struct score tmp, *datap;
	struct node *list = NULL;
	int i;

	for (i = 0; i < 8; i++) {
		tmp.id = i;
		tmp.ch = 100 - i;
		tmp.math = 100 - 2 * i;

		insert(&list, &tmp);
	}

	travel(list);
	printf("\n");
	delete(&list, 0);
	travel(list);
#if 0
	datap = find(list, 5);
	if (datap == NULL) {
		printf("Can not find.\n");
	} else {
		printf("%d %d %d\n", datap->id, datap->ch, datap->math);
	}
#endif

	destroy(list);

	return 0;
}
