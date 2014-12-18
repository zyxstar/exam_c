#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "darr.h"

DARR darr_create(int size)
{
	DARR handle = (DARR)malloc(sizeof(*handle));
	if(NULL == handle)
	{
		return NULL;
	}
	handle->data = NULL;
	handle->size = 0;
	handle->each = size;
	return handle;
}

int darr_insert(DARR head, const void *data)
{
	char *p = head->data;
	head->data = realloc(p,
		(head->size + 1)*head->each);
	if(NULL == head->data)
	{
		return -1;
	}
	memcpy(head->data + head->size*head->each,
			data, head->each);
	head->size++;
	return 0;
}

void *darr_find(DARR head, const void *key, darr_cmp *fun)
{
	int i;
	char *p = head->data;

	for(i = 0; i < head->size; i++)
	{
		if(0 == fun(p, key))
			return p;

		p += head->each;
	}
	return NULL;
}

static void** _store_find_data(int size, void *data){
	static void **store = NULL;
	if(size <= 0){
		free(store);
		store = NULL;
	}
	if(size == -1)
		return NULL;
	store = realloc(store, sizeof(void*) * (size + 1));
	store[size] = data;
	return store;
}

int darr_find_all(DARR head, const void *key, darr_cmp *fun, void ***find_data){
	int i, count = 0;
	char *p = head->data;

	for(i = 0; i < head->size; i++)
	{
		if(0 == fun(p, key)){
			*find_data = _store_find_data(count, p);
			count++;
		}
		p += head->each;
	}
	return count;
}


int darr_delete(DARR head, const void *key, darr_cmp *fun)
{
	int i;
	char *p = head->data;

	for(i = 0; i < head->size; i++)
	{
		if(0 == fun(p, key))
		{
			memmove(p,
					p + head->each,
					head->each*(head->size-i-1));
			head->size--;
			head->data = realloc(head->data,
						head->size*head->each);
			if(NULL == head->data)
			{
				return -2;
			}
			return 0;
		}

		p += head->each;
	}
	return -1;
}

void darr_display(DARR head, darr_print *fun)
{
	int i;
	char *p = head->data;

	for(i = 0; i < head->size; i++)
	{
		fun(p);
		p += head->each;
	}
}

void darr_dispose(DARR head)
{
	free(head->data);
	free(head);
	_store_find_data(-1, NULL);
}







