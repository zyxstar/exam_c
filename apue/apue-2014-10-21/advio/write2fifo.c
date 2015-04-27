#include <stdio.h>

#define BUFSIZE   128

int main(void)
{
	FILE *fp;
	char buf[BUFSIZE];
	char *retp;

	fp = fopen("ff", "w");
	/* if error */

	while (1) {
		retp = fgets(buf, BUFSIZE, stdin);
		/* if error */
		if (retp == NULL) {
			break;
		}

		fprintf(fp, "%s", buf);
		fflush(NULL);
	}

	fclose(fp);

	return 0;
}
