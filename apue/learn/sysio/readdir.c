#include <sys/types.h>
#include <dirent.h>

#include <stdio.h>

/* ./a.out path */
int main(int argc, char **argv)
{
	DIR *dir;
	struct dirent *entry;

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
		entry = readdir(dir);
		if (entry == NULL) {
			break;
		}

		printf("%d\t%s\n", entry->d_ino, entry->d_name);
	}

	closedir(dir);

	return 0;
}
