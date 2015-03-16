#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMDSIZE 4096

static void prompt(void)
{
	printf("[mysh]$ ");
	fflush(stdout);
}

static void getcmd(char *cmd, char **argv)
{
	int i = 0;

	fgets(cmd, CMDSIZE, stdin);

	argv[i] = strtok(cmd, " \t\n");
	for (i++; argv[i - 1] != NULL; i++) {
		argv[i] = strtok(NULL, " \t\n");
	}
}

static void myexit(char **argv)
{
	exit(0);
}

static void mycd(char **argv)
{
	chdir(argv[1]);
}

#define NAMESIZE 256
struct {
	void (*func)(char **);
	char name[NAMESIZE];
} internal_list[] = {
	{myexit, "exit"},
	{mycd, "cd"},
	{NULL, },
};

static int internal_ind(const char *name)
{
	int i;

	for (i = 0; internal_list[i].func != NULL; i++) {
		if (strcmp(name, internal_list[i].name) == 0) {
			return i;
		}
	}
	return -1;
}

int main(void)
{
	char cmd[CMDSIZE];
	char *argv[CMDSIZE / 2];
	pid_t pid;
	int ind;

	while (1) {
		prompt();

		getcmd(cmd, argv);
		if ((ind = internal_ind(argv[0])) != -1) {
			internal_list[ind].func(argv);
		} else {
			pid = fork();
			/* if error */
			if (pid == 0) {
				execvp(argv[0], argv);
				perror(argv[0]);
				exit(1);
			}
			wait(NULL);
		}
	}

	return 0;
}
