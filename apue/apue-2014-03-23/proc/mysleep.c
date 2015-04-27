#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	FILE *fp;

	fp = fopen("tmp", "a");
	/* if error */

	fprintf(fp, "pid = %d\n", getpid());
	fflush(fp);
	sleep(60);

	fclose(fp);

	return 0;
}
