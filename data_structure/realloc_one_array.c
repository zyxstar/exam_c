#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int i;
	int *p = NULL; // new
	int count = 0;
	int tmp;

	while(1)
	{
		if(1 != scanf("%d", &tmp))
			break;
		if(0 == tmp)
			break;

		count++;
		p = (int *)realloc(p, count*sizeof(int));
		if(NULL == p)
		{
			return 0;
		}
		p[count - 1] = tmp;
	}

	for(i = 0; i < count; i++)
	{
		printf("%d ", p[i]);
	}
	printf("\n");

	free(p);
	
	return 0;
}

/*
 *
 *
 *
 * */

