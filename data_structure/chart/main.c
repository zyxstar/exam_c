#include <stdio.h>

#include "chart.h"

int main(void)
{
	int i;
	int res;
	chart_t *p = NULL;
	chart_t data = 9;
	chart_t arr[] = {3,1,2,5,7,9,6,8};
	CHART head = NULL;

	head = chart_create(20);
	if(NULL == head)
	{
		return -1;
	}

	for(i = 0; i < sizeof(arr)/sizeof(*arr);i++)
	{
		chart_insert_tail(head, arr + i);
	}
	//chart_insert(head, 9, &data);
	//chart_delete(head, 8);
	p = chart_find_value(head, 4);
	if(p != NULL)
		printf("p = %d\n", *p);
	res = chart_find_pos(head, &data);
	printf("res = %d\n", res);

	chart_display(head);
	chart_dispose(head);
	
	return 0;
}
