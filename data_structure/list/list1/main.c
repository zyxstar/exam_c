#include <stdio.h>

#include "list.h"

int main(void)
{
	int i;
	PtrNode p;
	list_t data = 6;
	list_t arr[] = {3,1,2,5,7,9,6,8};
	LIST l = NULL;

	l = list_create();
	if(NULL == l)
		return -1;

	for(i = 0; i < sizeof(arr)/sizeof(*arr);i++)
	{
		//list_insert_head(l, arr + i);
		list_insert_tail(l, arr + i);
	}
#if 0
	p = list_find(l, &data);
	if(NULL == p)
		printf("not found\n");
	else
		printf("p->data = %d\n", p->data);
#endif
#if 0
	p = list_find_prev(l, &data);
	if(list_is_last(l, p))
		printf("not found\n");
	else
		printf("%d %d\n", p->data,p->next->data);
#endif

	list_delete(l, &data);

	list_display(l);
	list_dispose(l);
	
	return 0;
}
