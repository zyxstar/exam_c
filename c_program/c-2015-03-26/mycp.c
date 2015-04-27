#include <stdio.h>
#include <errno.h>

#define BUFSIZE 32

/* ./a.out src dest */
int main(int argc, char **argv)
{
	FILE *fps, *fpd;
	int ret;
	char buf[BUFSIZE];

	if (argc != 3) {
		fprintf(stderr, "argment...\n");
		goto argment_err;
	}

	fps = fopen(argv[1], "rb");
	if (fps == NULL) {
		perror(argv[1]);
		goto fopen_argv1_err;
	}

	fpd = fopen(argv[2], "wb");
	if (fpd == NULL) {
		perror(argv[2]);
		goto fopen_argv2_err;
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
fopen_argv2_err:
	fclose(fps);
fopen_argv1_err:
argment_err:
	return 1;
}
