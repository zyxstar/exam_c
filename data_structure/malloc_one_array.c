#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int i;
	int *p = NULL; // new
	int *q = NULL; // old
	int count = 0;
	int tmp;

	while(1)
	{
		if(1 != scanf("%d", &tmp))
			break;
		if(0 == tmp)
			break;

		count++;
		q = p;
		p = (int *)malloc(count * sizeof(int));
		if(NULL == p)
		{
			return 0;
		}
#if 0
		for(i = 0; i < count - 1; i++)
		{
			p[i] = q[i];
		}
#else
		memcpy(p, q, sizeof(int)*(count - 1));
#endif
		p[count - 1] = tmp;
		free(q);
		//q = NULL;
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

