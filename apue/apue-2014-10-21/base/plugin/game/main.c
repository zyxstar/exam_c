#include <sys/types.h>
#include <dirent.h>
#include <dlfcn.h>

#include <stdio.h>
#include <string.h>

#define OP_MAX    128
#define BUFSIZE   4096

struct op_st {
	void *handle;
	int (*op)(int, int);
	int (*sym)(void);
};

static int is_plugin(struct dirent *entry)
{
	char *last;

	last = strrchr(entry->d_name, '.');
	if (last == NULL) {
		return 0;
	}

	return !strcmp(last, ".plugin");
}

int main(void)
{
	struct op_st op[OP_MAX];
	int i, j;
	DIR *dir;
	struct dirent *entry;
	int ind;
	char path_buf[BUFSIZE];

	dir = opendir("./plugin");
	if (dir == NULL) {
		perror("./plugin");
		return 1;
	}

	ind = 0;
	while (ind < OP_MAX) {
		entry = readdir(dir);
		if (entry == NULL) {
			break;
		}

		if (is_plugin(entry)) {
			snprintf(path_buf, BUFSIZE, "./plugin/%s", entry->d_name);
			op[ind].handle = dlopen(path_buf, RTLD_LAZY);
			if (op[ind].handle == NULL) {
				fprintf(stderr, "dlopen(%s) err\n", path_buf);
			}
			op[ind].op = dlsym(op[ind].handle, "op");
			/* if error */
			op[ind].sym = dlsym(op[ind].handle, "sym");
			/* if error */
			ind++;
		}
	}

	closedir(dir);

	for (i = 0; i < ind; i++) {
		for (j = 0; j < ind; j++) {
			if (op[j].op(op[i].op(4, 5), 2) == 18) {
				printf("(4 %c 5) %c 2 = 18\n", op[i].sym(), op[j].sym());
			}
		}
	}

	for (i = 0; i < ind; i++) {
		dlclose(op[i].handle);
	}

	return 0;
}
