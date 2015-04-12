#include <sys/types.h>
#include <dirent.h>
#include <dlfcn.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH_LEN 256

static int isplugin(const char *name)
{
	int i;

	for (i = strlen(name); i >= 0; i--) {
		if (name[i] == '.') {
			break;
		}
	}
	if (i < 0) {
		return 0;
	}
	if (strcmp(name + i, ".plugin") == 0) {
		return 1;
	}
	return 0;
}

/* (2 [] 2) [] 9 = 13 */
int main(void)
{
	DIR *dir;
	struct dirent *entry;
	char **name;
	void **handle;
	int (**func)(int, int);
	int (**sym)(void);
	int plugin_nr;
	int i, j;
	char path[PATH_LEN];

	dir = opendir("./plugin");

	plugin_nr = 0;
	while (1) {
		entry = readdir(dir);
		if (entry == NULL) {
			break;
		}
		if (isplugin(entry->d_name)) {
			plugin_nr++;
		}
	}

	name = malloc(sizeof(*name) * plugin_nr);
	/* if error */
	handle = malloc(sizeof(*handle) * plugin_nr);
	/* if error */
	func = malloc(sizeof(*func) * plugin_nr);
	/* if error */
	sym = malloc(sizeof(*sym) * plugin_nr);
	/* if error */

	seekdir(dir, 0);
	i = 0;
	while (1) {
		entry = readdir(dir);
		if (entry == NULL) {
			break;
		}
		if (isplugin(entry->d_name)) {
			name[i++] = strdup(entry->d_name);
		}
	}

	closedir(dir);

	for (i = 0; i < plugin_nr; i++) {
		snprintf(path, PATH_LEN, "./plugin/%s", name[i]);
		handle[i] = dlopen(path, RTLD_LAZY);
		/* if error */
		func[i] = dlsym(handle[i], "op");
		sym[i] = dlsym(handle[i], "symbol");
	}

	for (i = 0; i < plugin_nr; i++) {
		for (j = 0; j < plugin_nr; j++) {
			if (func[j](func[i](2, 2), 9) == 13) {
				printf("(2 %c 2) %c 9 = 13\n", sym[i](), sym[j]());
			}
		}
	}

	for (i = 0; i < plugin_nr; i++) {
		dlclose(handle[i]);
	}

	return 0;
}
