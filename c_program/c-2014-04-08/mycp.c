#include <stdio.h>
#include <errno.h>

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
		perror(argv[1]);
		goto open_src_err;
	}

	fpd = fopen(argv[2], "wb");
	if (fpd == NULL) {
		perror(argv[2]);
                goto open_dest_err;
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
open_dest_err:
	fclose(fps);
open_src_err:
	return -1;
}
