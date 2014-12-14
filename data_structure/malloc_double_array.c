#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

int main(void)
{
	int i;
	int count = 0;
	char **p = NULL;
	char **q = NULL;
	char tmp[SIZE];

	while(1)
	{
		scanf("%s", tmp);
		if(0 == strcmp(tmp, "quit"))
			break;

		count++;
		q = p;
		p = (char **)malloc(count*sizeof(char*));
		if(NULL == p)
		{
			//free q count-1
			return -1;
		}
		memcpy(p, q, (count-1)*sizeof(char*));
		p[count-1] = (char *)malloc(strlen(tmp)+1);
		if(NULL == p[count - 1])
		{
			//free q count-1
			return -2;
		}
		strcpy(p[count-1], tmp);

		free(q);
	}

	for(i = 0; i < count; i++)
	{
		printf("%s ", p[i]);
	}
	printf("\n");
	
	for(i = 0; i < count; i++)
	{
		free(p[i]);
	}
	free(p);

	return 0;
}
