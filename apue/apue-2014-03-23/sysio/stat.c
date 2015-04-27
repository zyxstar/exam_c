#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdio.h>

void print_mode(mode_t m)
{
	switch (m & S_IFMT) {
	case S_IFSOCK:
		printf("s");
		break;
	case S_IFLNK:
		printf("l");
		break;
	case S_IFREG:
		printf("-");
		break;
	case S_IFBLK:
		printf("b");
		break;
	case S_IFDIR:
		printf("d");
		break;
	case S_IFCHR:
		printf("c");
		break;
	case S_IFIFO:
		printf("p");
		break;
	}

	switch ((m & S_IRWXU) >> 6) {
	case 0:
		printf("---");
		break;
	case 1:
		printf("--x");
		break;
	case 2:
		printf("-w-");
		break;
	case 3:
		printf("-wx");
		break;
	case 4:
		printf("r--");
		break;
	case 5:
		printf("r-x");
		break;
	case 6:
		printf("rw-");
		break;
	case 7:
		printf("rwx");
		break;
	}

	switch ((m & S_IRWXG) >> 3) {
	case 0:
		printf("---");
		break;
	case 1:
		printf("--x");
		break;
	case 2:
		printf("-w-");
		break;
	case 3:
		printf("-wx");
		break;
	case 4:
		printf("r--");
		break;
	case 5:
		printf("r-x");
		break;
	case 6:
		printf("rw-");
		break;
	case 7:
		printf("rwx");
		break;
	}

	switch ((m & S_IRWXO) >> 0) {
	case 0:
		printf("---");
		break;
	case 1:
		printf("--x");
		break;
	case 2:
		printf("-w-");
		break;
	case 3:
		printf("-wx");
		break;
	case 4:
		printf("r--");
		break;
	case 5:
		printf("r-x");
		break;
	case 6:
		printf("rw-");
		break;
	case 7:
		printf("rwx");
		break;
	}

}

/* $ ./a.out path */
int main(int argc, char **argv)
{
	int ret;
	struct stat buf;

	if (argc != 2) {
		fprintf(stderr, "argment...\n");
		return 1;
	}

	ret = stat(argv[1], &buf);
	/* if error */

	//printf("mode:   %x\n", buf.st_mode);
	printf("mode:   ");
	print_mode(buf.st_mode);
	printf("\n");
	printf("ino:    %d\n", buf.st_ino);
	printf("nlink:  %d\n", buf.st_nlink);
	printf("uid:    %d\n", buf.st_uid);
	printf("rdev:   %x\n", buf.st_rdev);
	printf("size:   %d\n", buf.st_size);

	printf("time: %u, %u, %u\n", buf.st_atime, buf.st_mtime, buf.st_ctime);

	return 0;
}
