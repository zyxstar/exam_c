#include <stdio.h>

int main(void)
{
	FILE *fp;

	fp = fopen("tmp", "w");

	fprintf(fp, "hello\n");

	fclose(fp);

	return 0;
}
