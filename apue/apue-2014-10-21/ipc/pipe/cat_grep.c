/* $ cat /etc/passwd | grep hsienmu */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	pid_t pid;
	int fd[2];

	pipe(fd);
	/* if error */

	pid = fork();
	/* if error */
	if (pid == 0) {
		/* cat */
		close(fd[0]);
		if (fd[1] != 1) {
			dup2(fd[1], 1);
			close(fd[1]);
		}

		execlp("cat", "cat", "/etc/passwd", NULL);
		perror("cat");
		exit(1);
	}

	pid = fork();
	/* if error */
	if (pid == 0) {
		/* grep */
		close(fd[1]);
		if (fd[0] != 0) {
			dup2(fd[0], 0);
			close(fd[0]);
		}

		execlp("grep", "grep", "hsienmu", NULL);
		perror("grep");
                exit(1);
	}

	close(fd[0]);
	close(fd[1]);

	wait(NULL);
	wait(NULL);

	return 0;
}
