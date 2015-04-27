#include <stdio.h>
#include <stdlib.h>

struct node_st {
	int data;
	struct node_st *next;
};

static struct node_st *list = NULL;

static int is_empty(void)
{
	if (list == NULL) {
		return 1;
	}
	return 0;
}

static int is_full(void)
{
	return 0;
}

int push(int data)
{
	struct node_st *newnode;

	if (is_full()) {
		return -1;
	}

	newnode = malloc(sizeof(*newnode));
	/* if error */

	newnode->data = data;
	newnode->next = list;
	list = newnode;

	return 0;
}

int pop(int *data)
{
	struct node_st *save;

	if (is_empty()) {
		return -1;
	}

	*data = list->data;
	save = list;
	list = save->next;
	free(save);

	return 0;
}

int main(void)
{
	int arr[] = {3,2,1,6,7};
	int i;
	int data;
	int ret;

	for (i = 0; i < sizeof(arr) / sizeof(*arr); i++) {
		ret = push(arr[i]);
		if (ret == -1) {
			printf("stack full.\n");
			break;
		}
	}

	while (1) {
		ret = pop(&data);
		if (ret == -1) {
			printf("stack empty.\n");
			break;
		}
		printf("%d ", data);
	}
	printf("\n");

	return 0;
}
