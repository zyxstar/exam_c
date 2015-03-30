#include <unistd.h>

#include <stdio.h>

/* cat /etc/passwd | more */
int main(void)
{
	pid_t pid;
	int fd[2];

	pipe(fd);

	/* cat */
	pid = fork();
	/* if error */
	if (pid == 0) {
		if (fd[1] != 1) {
			dup2(fd[1], 1);
			close(fd[1]);
		}
		close(fd[0]);
		execlp("cat", "cat", "/etc/passwd", NULL);
		perror("cat: /etc/passwd");
		return 1;
	}

	/* more */
	if (fd[0] != 0) {
		dup2(fd[0], 0);
		close(fd[0]);
	}
	close(fd[1]);
	execlp("more", "more", NULL);
	perror("more");

	return 1;
}
