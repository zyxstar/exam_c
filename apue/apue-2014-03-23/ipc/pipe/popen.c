#include <stdio.h>

#define BUFSIZE 1024

int main(void)
{
	FILE *fp;
	char buf[BUFSIZE];
	char *retp;

	fp = popen("cat /etc/passwd", "r");
	/* if error */

	printf("\033[31m");

	while (1) {
		retp = fgets(buf, BUFSIZE, fp);
		if (retp == NULL) {
			break;
		}
		printf("%s", buf);
		printf("sui bian\n");
	}

	printf("\033[0m");

	pclose(fp);

	return 0;
}
