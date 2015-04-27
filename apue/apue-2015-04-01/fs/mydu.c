#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define PATHSIZE		128

static int path_noloop(const char *path)
{
//	path = adfasdf/asdf/df/df/dfdf/..aaa...
	char *pos;

	pos = strrchr(path,'/');
	if(pos == NULL)
		exit(1);

	if(strcmp(pos+1,".") == 0 || strcmp(pos+1,"..") == 0)
		return 0;
	return 1;
}

static int64_t mydu(const char *path)
{
	static struct stat statres;
	int i;
	static char nextpath[PATHSIZE];
	glob_t globres;
	int64_t sum = 0;

	if(lstat(path,&statres) < 0)
	{
		perror("lstat()");
		exit(1);
	}

	if(!S_ISDIR(statres.st_mode))
		return statres.st_blocks;

	// path is a dir
	// path = adsf/asdf/sdf/asdf/sdf
	
	strncpy(nextpath,path,PATHSIZE);
	strncat(nextpath,"/*",PATHSIZE);
	glob(nextpath,0,NULL,&globres);

	strncpy(nextpath,path,PATHSIZE);
    strncat(nextpath,"/.*",PATHSIZE);
	glob(nextpath,GLOB_APPEND,NULL,&globres);

	sum = statres.st_blocks;

	for(i = 0 ; i < globres.gl_pathc; i++)
	{
		if(path_noloop(globres.gl_pathv[i]))
			sum += mydu(globres.gl_pathv[i]);
	}


	return sum;
}

int main(int argc, char **argv)
{
	printf("%lld\n",mydu(argv[1])/2);

	exit(0);
}



