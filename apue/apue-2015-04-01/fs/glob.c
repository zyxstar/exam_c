#include <stdio.h>
#include <stdlib.h>
#include <glob.h>

/*
int errfunc(const char *epath, int eerrno)
{
	puts(epath);

	strerror(eerrno)

}
*/

#define PAT		"/etc/a*.conf"

int main()
{
	glob_t globres;
	int err,i;

	err = glob(PAT,0,NULL,&globres);	
	if(err)
	{
		printf("glob()error:code = %d\n",err);
		exit(1);
	}

	for(i = 0 ; i < globres.gl_pathc; i++)
		puts(globres.gl_pathv[i]);
	
	globfree(&globres);

	exit(0);
}






