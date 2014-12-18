#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 单向 无头结点 非循环 链表

#define NAMESIZE 25

typedef struct stuinfo {
	int id;
	char name[NAMESIZE];
	int score;
}DATA;

typedef struct list_node {
	DATA data;
	struct list_node *next;
}*LIST;

int list_insert(LIST *l, const DATA *data)
{
	// init node
	struct list_node *cur;
	cur =(struct list_node*)malloc(sizeof(*cur));
	if(NULL == cur)
	{
		return -1;
	}
	cur->data = *data;
	cur->next = NULL;

	// insert list
	if(*l == NULL)
	{
		//cur->next = *l;
		*l = cur;
		return 0;
	}
	if((*l)->data.id < cur->data.id)
	{
		cur->next = *l;
		*l = cur;
		return 0;
	}
	struct list_node *p = *l;
	struct list_node *q;
	for(; p != NULL; q = p, p = p->next)
	{
		if(p->data.id < cur->data.id)
		{
			break;
		}
	}
	cur->next = p;
	q->next = cur;
	return 0;
}

static void print_s(const DATA *p)
{
	printf("%d %s %d\n", 
			p->id,
			p->name,
			p->score);
}

void list_display(LIST l)
{
	struct list_node *p = l;

	for(; p != NULL; p = p->next)
	{
		print_s(&p->data);
	}
}

void list_dispose(LIST l)
{
	struct list_node *p = l;
	struct list_node *q;

	while(p != NULL)
	{
		q = p;
		p = p->next;
		free(q);
	}
}

struct stuinfo *list_find(LIST l, int id)
{
	struct list_node *p = l;

	for(; p != NULL; p = p->next)
	{
		if(p->data.id == id)
			return &p->data;
	}
	return NULL;
}

int list_delete(LIST *l, int id)
{
	struct list_node *p = *l;
	struct list_node *q;

	if((*l) == NULL)
		return -1;
	if((*l)->data.id == id)
	{
		*l = p->next;
		free(p);
		return 0;
	}
	for(; p != NULL; q = p, p = p->next)
	{
		if(p->data.id == id)
		{
			q->next = p->next;
			free(p);
			return 0;
		}
	}
	return -2;
}

int main(void)
{
	int i;
	DATA tmp;
	DATA *stup = NULL;
	LIST head = NULL;
	
	for(i = 0; i < 6; i++)
	{
		// init stu info
		tmp.id = i;
		snprintf(tmp.name, NAMESIZE,"stu%d",i);
		tmp.score = 100;
		// insert list
		list_insert(&head, &tmp);
	}
	/*
	tmp.id = 8;
	list_insert(&head, &tmp);
	tmp.id = 6;
	list_insert(&head, &tmp);
	*/
	stup = list_find(head, 3);
	if(stup == NULL)
		printf("not found\n");
	else
		print_s(stup);

	list_delete(&head, 0);

	list_display(head);
	list_dispose(head);

	return 0;
}
