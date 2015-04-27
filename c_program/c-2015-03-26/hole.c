#include <stdio.h>

int main(void)
{
	FILE *fp;

	fp = fopen("./tmp", "w");
	/* if error */

	fseek(fp, 1024 * 1024 * 1024, SEEK_SET);
	fprintf(fp, "hello\n");

	fclose(fp);

	return 0;
}
