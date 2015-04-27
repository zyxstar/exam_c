#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <glob.h>
#include <string.h>


#define DELIMS		" \t\n"

struct cmd_st
{
	glob_t globres;
};

static void prompt(void)
{
	printf("mysh-0.1$ ");
}

int parse(char *line,struct cmd_st *res)
{
	// cmd opt    opt    !opt !opt
	char *tok;	
	int i = 0;

	while(1)
	{
		tok = strsep(&line,DELIMS);
		if(tok == NULL)
			break;
		if(tok[0] == '\0')
			continue;
		
		// "cmd" "opt" "!opt"
	
		if(glob(tok,GLOB_NOCHECK|GLOB_APPEND*i,NULL,&res->globres) != 0)
			return -1;
		i = 1;
	}

	return 0;
}

static void parse_free(struct cmd_st *cmd)
{	
	globfree(&cmd->globres);
}

int main()
{
	pid_t pid;
	char *linebuf = NULL;
	size_t linebuf_size = 0;
	struct cmd_st cmd;

	while(1)
	{
		prompt();
		
		if(getline(&linebuf,&linebuf_size,stdin) < 0)
			break;

		parse(linebuf,&cmd);		

		if(0/*内部命令*/)
		{
			/*do sth*/			
		}		
		else	/*外部命令*/
		{
			pid = fork();
			if(pid < 0)
			{
				perror("fork()");
				exit(1);
			}

			if(pid == 0)	// child
			{
				execvp(cmd.globres.gl_pathv[0],cmd.globres.gl_pathv);
				perror("exec()");
				exit(1);
			}		
			else
				wait(NULL);
		}

		parse_free(&cmd);	
	
	}

	exit(0);
}


