#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

LIST list_create()
{
	LIST l = (LIST)malloc(sizeof(*l));
	if(NULL == l)
		return NULL;

	// l->data = ;
	l->next = NULL; // 非循环
	// l->next = l; // 循环
	return l;
}

int list_is_empty(LIST l)
{
	return (l->next == NULL);
}

int list_is_last(LIST l, Position p)
{
	return (p->next == NULL);
	// return (p->next == l);
}

int list_insert(LIST l, const list_t *data, Position prev)
{
	PtrNode cur = (PtrNode)malloc(sizeof(*cur));
	if(NULL == cur)
	{
		return -1;
	}
	cur->data = *data;
	//cur->next = NULL;

	cur->next = prev->next;
	prev->next = cur;
	return 0;
}

int list_insert_head(LIST l, const list_t *data)
{
	return list_insert(l, data, l);
}

int list_insert_tail(LIST l, const list_t *data)
{
	Position tail = l;

	for(;tail->next != NULL; tail = tail->next);

	return list_insert(l, data, tail);
}

static int list_cmp(const list_t *data, const list_t *key)
{
	return (*data - *key);
}

PtrNode list_find(LIST l, const list_t *key)
{
	PtrNode p = l->next;

	for(;p != NULL && list_cmp(&p->data, key);
					p = p->next);

	return p;
}

PtrNode list_find_prev(LIST l,const list_t *key)
{
	PtrNode p = l;

	for(; p->next != NULL && list_cmp(&p->next->data, key); p = p->next);

	return p;
}

int list_delete(LIST l, const list_t *key)
{
	PtrNode p = list_find_prev(l, key);

	if(!list_is_last(l, p))
	{
		PtrNode q = p->next;
		p->next = q->next;
		free(q);
		return 0;
	}
	return -1;
}

static void print_l(const list_t *data)
{
	printf("%d\n", *data);
}

void list_display(LIST l)
{
	Position p = l->next;

	for(; p != NULL; p = p->next)
	{
		print_l(&p->data);
	}
}

void list_dispose(LIST l)
{
	PtrNode p = l->next;
	PtrNode q;

	while(p != NULL)
	{
		q = p;
		p = p->next;
		free(q);
	}
	free(l);
}









