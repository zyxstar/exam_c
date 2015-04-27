#include <stdio.h>

#define BUFSIZE 32

/* $ ./a.out src dest */
int main(int argc, char **argv)
{
	FILE *fps, *fpd;
	char buf[BUFSIZE];
	int ret;

	if (argc != 3) {
		fprintf(stderr, "argment...\n");
		return 1;
	}

	fps = fopen(argv[1], "rb");
	if (fps == NULL) {
		fprintf(stderr, "fopen(src) failed.\n");
		goto fopen_src;
	}

	fpd = fopen(argv[2], "wb");
	if (fpd == NULL) {
                fprintf(stderr, "fopen(dest) failed.\n");
                goto fopen_dest;
        }

	while (1) {
		ret = fread(buf, 1, BUFSIZE, fps);
		if (ret == 0) {
			break;
		}

		fwrite(buf, 1, ret, fpd);
	}

	fclose(fpd);
	fclose(fps);

	return 0;



	fclose(fpd);
fopen_dest:
	fclose(fps);
fopen_src:
	return 1;
}
