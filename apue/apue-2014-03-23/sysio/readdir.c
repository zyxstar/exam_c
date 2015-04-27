#include <sys/types.h>
#include <dirent.h>

#include <stdio.h>

/* $ ./a.out dirname */
int main(int argc, char **argv)
{
	DIR *dir;
	struct dirent *direntry;

	if (argc != 2) {
		fprintf(stderr, "argment...\n");
		return 1;
	}

	dir = opendir(argv[1]);
	if (dir == NULL) {
		perror(argv[1]);
		return 1;
	}

	while (1) {
		direntry = readdir(dir);
		if (direntry == NULL) {
			break;
		}

		printf("%d %s\n", direntry->d_ino, direntry->d_name);
	}

	closedir(dir);

	return 0;
}
