#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

/* $ cat /etc/passwd | grep hsienmu */
int main(void)
{
	pid_t pid_cat, pid_grep;
	int fd[2];

	pipe(fd);

	pid_cat = fork();
	/* if error */
	if (pid_cat == 0) {
		close(fd[0]);
		if (fd[1] != 1) {
			dup2(fd[1], 1);
			close(fd[1]);
		}
		execlp("cat", "cat", "/etc/passwd", NULL);

		perror("exec(cat)");
		exit(1);
	}

	pid_grep = fork();
	/* if error */
	if (pid_grep == 0) {
		close(fd[1]);
		if (fd[0] != 0) {
			dup2(fd[0], 0);
			close(fd[0]);
		}
		execlp("grep", "grep", "hsienmu", NULL);

		perror("execlp(grep)");
                exit(1);
	}

	close(fd[0]);
	close(fd[1]);

	wait(NULL);
	wait(NULL);

	return 0;
}
