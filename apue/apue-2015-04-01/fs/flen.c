#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
/*
 *
 *计算文件字符的个数或文件的大小
 * */
static off_t flen(const char *pathname)
{
	struct stat statres;

	if(stat(pathname,&statres) < 0)
	{
		perror("stat()");
		exit(1);
	}

	return statres.st_size;
}

int main(int argc,char **argv)
{
	if(argc < 2)
	{
		fprintf(stderr,"Usage...\n");
		exit(1);
	}

	printf("%lld\n",(long long)flen(argv[1]));

	exit(0);

}




