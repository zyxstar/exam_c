#include <stdio.h>
#include <stdlib.h>
#include <shadow.h>
#include <unistd.h>


int main(int argc,char **argv)
{
	struct spwd *shadline;
	char *pwd,*crypted_pass;

	if(argc < 2)
	{
		fprintf(stderr,"Usage...\n");
		exit(1);
	}


	shadline = getspnam(argv[1]);
	if(shadline == NULL)
	{
		perror("getspnam()");
		exit(1);
	}
	
	pwd = getpass("PASSWORD:");
	if(pwd == NULL)
	{
		perror("getpass()");
		exit(1);
	}
		printf("%s\n",shadline->sp_pwdp);
	crypted_pass = crypt(pwd,shadline->sp_pwdp);
     
	if(strcmp(crypted_pass,shadline->sp_pwdp) == 0)
		puts("ok!");
	else 
		puts("failed!");


	exit(0);
}



