#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <errno.h>


/* ./a.out src dest */
int main(int argc, char **argv)
{
	FILE *fdr, *fdw;
	int retr;
	int size = pow(2, atoi(argv[3]));
	char buf[size];

	if (argc != 4) {
		fprintf(stderr, "argment...\n");
		return 1;
	}

	printf("buffer size is: %d\n", size);

	fdr = fopen(argv[1], "r");
	if (fdr == NULL) {
		perror(argv[1]);
		goto open_fdr_err;
	}

	fdw = fopen(argv[2], "w");
	if (fdw == NULL) {
		perror(argv[2]);
		goto open_fdw_err;
	}

	while (1) {
		retr = fread(buf, 1, size, fdr);
		if (retr == 0) {
			break;
		}
		fwrite(buf, 1, retr, fdw);
		fflush(fdw);
	}

	fclose(fdw);
	fclose(fdr);

	return 0;



read_err:
write_err:
	fclose(fdw);
open_fdw_err:
	fclose(fdr);
open_fdr_err:
	return 1;
}
