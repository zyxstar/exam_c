#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>

int main(int argc,char **argv)
{
	struct passwd *pwd;

	if(argc < 2)
	{
		fprintf(stderr,"Usage...\n");
		exit(1);
	}
	
	pwd = getpwuid(atoi(argv[1]));
	if(pwd == NULL)
	{
		perror("getpwuid()");
		exit(1);
	}

	puts(pwd->pw_name);


	exit(0);
}


