#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chart.h"

CHART chart_create(int capacity)
{
	CHART handle = (CHART)malloc(sizeof(*handle));
	if(NULL == handle)
	{
		return NULL;
	}
	handle->data = (chart_t*)malloc(capacity*sizeof(chart_t));
	if(NULL == handle->data)
	{
		free(handle);
		return NULL;
	}
	handle->size = 0;
	handle->capacity = capacity;

	return handle;
}

int chart_is_empty(CHART head)
{
	return (0 == head->size);
}

int chart_is_full(CHART head)
{
	return (head->capacity == head->size);
}

void chart_make_empty(CHART head)
{
	// memset(head->data, 0, head->capacity*sizeof(chart_t));
	head->size = 0;
}

int chart_insert_tail(CHART head, const chart_t *data)
{
	if(chart_is_full(head))
		return -1;
	
	head->data[head->size] = *data;
	head->size++;
	return 0;
}

int chart_insert(CHART head, int pos, const chart_t *data)
{
	int lo = head->size;
	if(chart_is_empty(head) == 1 && pos == 1)
	{
		head->data[0] = *data;
		head->size++;
		return 0;
	}
	if(chart_is_full(head) == 1 || pos > lo + 1)
	{
		return -1;
	}
	memmove(head->data + pos,
			head->data + (pos - 1),
			sizeof(chart_t)*(lo-pos+1));
	head->data[pos - 1] = *data;
	head->size++;
	return 0;
}

int chart_delete(CHART head, int pos)
{
	int lo = head->size;
	if(pos > lo)
		return -1;

	memmove(head->data + pos - 1,
			head->data + pos,
			sizeof(chart_t)*(lo-pos));
	head->size--;
	return 0;
}

void *chart_find_value(CHART head, int pos)
{
	if(pos > head->size)
		return NULL;
	return head->data + (pos - 1);
}

static int chart_cmp(const chart_t *key, const chart_t *data)
{
	return (*key - *data);
}

int chart_find_pos(CHART head, const chart_t *data)
{
	int i;

	for(i = 0; i < head->size; i++)
	{
		if(0 == chart_cmp(head->data+i, data))
			return (i + 1);
	}
	return 0;
}

static void sort_up(chart_t *data, int size)
{}

static void sort_dn(chart_t *data, int size)
{}

int chart_sort(CHART head, int mode)
{
	if(SORTDN == mode)
	{
		sort_up(head->data, head->size);
		return 0;
	}
	else if(SORTUP == mode)
	{
		sort_dn(head->data, head->size);
		return 0;
	}
	else
	{
		return -1;
	}
}

static void print(const chart_t *data)
{
	printf("%d ", *data);
}

void chart_display(CHART head)
{
	int i;

	for(i = 0; i < head->size; i++)
	{
		print(head->data + i);
	}
	printf("\n");
}

void chart_dispose(CHART head)
{
	free(head->data);
	free(head);
}







