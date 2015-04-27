#include <stdio.h>

#define BUFSIZE   32

/* ./a.out src dest */
int main(int argc, char **argv)
{
	FILE *fpr, *fpw;
	char buf[BUFSIZE];
	int ret;

	if (argc != 3) {
		fprintf(stderr, "argment...\n");
		return 1;
	}

	fpr = fopen(argv[1], "rb");
	if (fpr == NULL) {
		perror(argv[1]);
		return 1;
	}

	fpw = fopen(argv[2], "wb");
	if (fpw == NULL) {
                perror(argv[2]);
		fclose(fpr);
                return 1;
        }

	while (1) {
		ret = fread(buf, 1, BUFSIZE, fpr);
		if (ret == 0) {
			break;
		}

		fwrite(buf, 1, ret, fpw);
	}

	fclose(fpw);
	fclose(fpr);

	return 0;
}
