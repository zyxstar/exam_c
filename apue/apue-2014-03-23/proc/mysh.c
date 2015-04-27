#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 1024

void print_prompt(void)
{
	printf("[mysh]$ ");
	fflush(NULL);
}

void buf2argv(char *buf, char **argv)
{
	int i = 0;

	argv[i] = strtok(buf, " \t\n");
	while (argv[i] != NULL) {
		i++;
		argv[i] = strtok(NULL, " \t\n");
	}
}

#define NAME_SIZE 256
struct internal_cmd_st {
	int (*func)(char **);
	char *name;
};

int my_exit(char **argv)
{
	exit(0);
}

int my_cd(char **argv)
{
	return chdir(argv[1]);
}

struct internal_cmd_st internal_list[] = {
	{my_exit, "exit"},
	{my_cd, "cd"},
	{NULL, NULL},
};

int is_internal_cmd(char *name)
{
	int i;

	for (i = 0; internal_list[i].name != NULL; i++) {
		if (strcmp(name, internal_list[i].name) == 0) {
			return 1;
		}
	}
	return 0;
}

int internal_cmd(char **argv)
{
	int i;

	for (i = 0; internal_list[i].name != NULL; i++) {
		if (strcmp(argv[0], internal_list[i].name) == 0) {
			return internal_list[i].func(argv);
		}
	}

	return -1;
}

void job(void)
{
	char buf[BUFSIZE];
	char *argv[BUFSIZE / 2];
	pid_t pid;

	while (1) {
		print_prompt();

		fgets(buf, BUFSIZE, stdin);
		buf2argv(buf, argv);

		if (is_internal_cmd(argv[0])) {
			internal_cmd(argv);		
		} else {
			pid = fork();
			/* if error */
			if (pid == 0) {
				execvp(argv[0], argv);
				perror("exec()");
				exit(1);
			}
		}
		wait(NULL);
	}
}

int interp(const char *path)
{
	FILE *fp;
	char buf[BUFSIZE];
	char *argv[BUFSIZE / 2];
	pid_t pid;
	char *retp;

	fp = fopen(path, "r");
	if (fp == NULL) {
		perror(path);
		exit(1);
	}

	while (1) {
		retp = fgets(buf, BUFSIZE, fp);
		if (retp == NULL) {
			break;
		}
		buf2argv(buf, argv);

		if (argv[0] == NULL || argv[0][0] == '#') {

		} else if (is_internal_cmd(argv[0])) {
			internal_cmd(argv);		
		} else {
			pid = fork();
			/* if error */
			if (pid == 0) {
				execvp(argv[0], argv);
				perror("exec()");
				exit(1);
			}
		}
		wait(NULL);
	}

	fclose(fp);
	return 0;
}

int main(int argc, char **argv)
{

	if (argc == 1) {
		job();
	} else {
		interp(argv[1]);
	}

	return 0;
}
