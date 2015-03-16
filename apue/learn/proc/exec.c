#include <unistd.h>

/* ls -l */
int main(void)
{
	char *argv[] = {"ls", "-l", NULL};

	//execlp("ls", "ls", "-l", NULL);
	//execl("/bin/ls", "ls", "-l", NULL);
	execvp("ls", argv);

	perror("exec()");
	return 1;
}
