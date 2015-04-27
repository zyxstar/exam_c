#include <stdio.h>

#define BUFSIZE 32

int main(void)
{
	FILE *fp;
	char buf[BUFSIZE];
	char *retp;

	fp = popen("cat /etc/passwd", "r");
	/* if error */

	while (1) {
		retp = fgets(buf, BUFSIZE, fp);
		if (retp == NULL) {
			break;
		}
		printf("\033[31m%s\033[0m", buf);
		fflush(stdout);
	}

	pclose(fp);

	return 0;
}
