#include <stdio.h>

#define BUFSIZE 128

int main(void)
{
	FILE *fp;
	char buf[BUFSIZE];

	fp = popen("cat /etc/passwd | grep ftp", "r");
	/* if error */

	fgets(buf, BUFSIZE, fp);
	printf("\033[31m%s\033[0m\n", buf);

	pclose(fp);

	return 0;
}
