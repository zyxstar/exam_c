#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc,char *argv[])
{

	FILE *fp;
	
	if(argc < 2)
	{
		fprintf(stderr,"Usage:%s <pathname>\n",argv[0]);
		return -1;
	}

	fp = fopen(argv[1],"w");
	if(fp == NULL)
	{
//		printf("errno = %d\n",errno);
//		perror("fopen()");
		printf("fopen():%s\n",strerror(errno));
		return -1;
	}

	puts("ok!");
	
	fclose(fp);	

	return 0;
}




