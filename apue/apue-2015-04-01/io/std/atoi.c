#include <stdio.h>
#include <stdlib.h>


int main()
{
//	char str[] = "a1a23a456bc";

//	printf("%d\n",atoi(str));
	
	int i = 2015,j = 4,m = 13;
	char str[] = "Mon";
	char dest[1024];

	snprintf(dest,1024,"%d-%d-%d %s",i,j,m,str);
	
	puts(dest);


	exit(0);
}






