#include <unistd.h>

#include <stdio.h>

int main(void)
{
	char *argv[] = {"ls", "--color=auto", "/", NULL};

	//execlp("ls", "ls", "/", NULL);
	//execl("./mysleep", "xxx", NULL);
	execvp("ls", argv);

	printf("\033[31merror\033[0m\n");

	return 1;
}
