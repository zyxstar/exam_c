#include <stdio.h>

int sort(char *name[5])
{
	FILE *fp, *fpw[2];
	int data[2];
	int nr;

	fp = fopen(name[0], "r");
	/* if error */

	fpw[0] = fopen(name[1], "w");
	/* if error */
	fpw[1] = fopen(name[2], "w");
	/* if error */

	while (1) {
		for (i = 0; i < 2; i++) {
			ret = fread(data, sizeof(int), 2, fp);
			if (ret == 0) {
				goto out;
			}

			if (ret == 1) {
				fwrite(data, sizeof(int), 1, fpw[i]);
				goto out;
			}
			if (data[0] < data[1]) {
				fwrite(data, sizeof(int), 2, fpw[i]);
			} else {
				fwrite(data + 1, sizeof(int), 1, fpw[i]);
				fwrite(data, sizeof(int), 1, fpw[i]);
			}
		}
	}

	fclose(fpw[1]);
	fclose(fpw[0]);
	fclose(fp);

out:
	nr = 2;
	while () {

	}
}

int main(void)
{
	int data[18] = {4,9,3,44,99,88,8,33,2,22,5,55,66,6,7,77,1,11,};
	FILE *fp;
	char *name[] = {"file", "file1", "file2", "file3", "file4", };

	fp = fopen("file", "w");
	/* if error */
	fwrite(data, 18, sizeof(int), fp);
	/* if error */
	fclose(fp);

	sort(name);

	fp = fopen("file", "r");
	fread(data, 18, sizeof(int), fp);
	fclose(fp);

	for (i = 0; i < 18; i++) {
		printf("%d ", data[i]);
	}
	printf(\n);

	return 0;
}
