#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#define PATH	"/tmp"

int main()
{
	DIR *dirp;
	struct dirent *cur;

	dirp = opendir(PATH);	
	if(dirp == NULL)
	{
		perror("opendir()");
		exit(1);
	}

	while((cur = readdir(dirp)) != NULL)
		puts(cur->d_name);
	

	closedir(dirp);

	exit(0);
}



