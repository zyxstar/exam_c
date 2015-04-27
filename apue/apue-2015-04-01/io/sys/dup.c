#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FNAME		"/tmp/out"

int main()
{
	int fd;

	fd = open(FNAME,O_WRONLY|O_CREAT|O_TRUNC,0600);
	if(fd < 0)
	{
		perror("open()");
		exit(1);
	}

//	close(1);
//	dup(fd);
	
	dup2(fd,1);

	if(fd != 1)
		close(fd);


/***************************************/
	
	puts("hello!");

	exit(0);
}


