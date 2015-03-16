#include <sys/times.h>
#include <unistd.h>

#include <stdio.h>

int main(int argc, char **argv)
{
	clock_t start, end;
	struct tms tms;
	pid_t pid;

	start = times(&tms);

	pid = fork();
	/* if error */
	if (pid == 0) {
		execvp(argv[1], argv + 1);
		perror(argv[1]);
		return 1;
	}

	wait(NULL);
	end = times(&tms);

	//printf("%d\n", sysconf(_SC_CLK_TCK));
	printf("real:\t%f\n", (double)(end - start) / sysconf(_SC_CLK_TCK));
	printf("user:\t%f\n", (double)tms.tms_cutime / sysconf(_SC_CLK_TCK));
	printf("sys:\t%f\n", (double)tms.tms_cstime / sysconf(_SC_CLK_TCK));

	return 0;
}
