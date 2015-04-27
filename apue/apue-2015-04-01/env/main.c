#include <stdio.h>

// pmap  pid

int main()
{
	int i = 1;
	int *p = NULL;
	static int j = 10;
	
	p = malloc(sizeof(int));

	printf("",&i,&j,p);


	getchar();

	return 0;
}




