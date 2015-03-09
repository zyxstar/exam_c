#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdio.h>

static void print_perm_(mode_t mode)
{
	switch (mode & 07) {
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

static void print_perm(mode_t mode)
{
	int i;

	print_perm_(mode >> 6);
	print_perm_(mode >> 3);
	print_perm_(mode >> 0);
}

/* ./a.out path */
int main(int argc, char **argv)
{
	struct stat st;
	int ret;

	if (argc != 2) {
		fprintf(stderr, "argment...\n");
		return 1;
	}

	ret = stat(argv[1], &st);
	if (ret == -1) {
		perror(argv[1]);
		return 1;
	}

	printf("ino: %d\n", st.st_ino);

	//printf("mode: %x\n", st.st_mode);
	printf("mode: ");
	switch (st.st_mode & S_IFMT) {
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
	print_perm(st.st_mode);
	printf("\n");

	printf("nlink: %d\n", st.st_nlink);
	printf("uid: %d, gid: %d\n", st.st_uid, st.st_gid);
	printf("rdev: %d\n", st.st_rdev);
	printf("size: %d\n", st.st_size);
	printf("atime: %d\n", st.st_atime);
	printf("mtime: %d\n", st.st_mtime);
	printf("ctime: %d\n", st.st_ctime);

	return 0;
}
