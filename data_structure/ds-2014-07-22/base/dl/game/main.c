#include <dlfcn.h>

#include <stdio.h>

int main(void)
{
	char *filename[] = {"./plugin/add.plugin", "./plugin/sub.plugin", "./plugin/mul.plugin", "./plugin/div.plugin"};
	void *handle[sizeof(filename) / sizeof(*filename)];
	int (*op[sizeof(filename) / sizeof(*filename)])(int, int);
	int (*sym[sizeof(filename) / sizeof(*filename)])(void);
	int i, j;

	for (i = 0; i < sizeof(filename) / sizeof(*filename); i++) {
		handle[i] = dlopen(filename[i], RTLD_LAZY);
		/* if error */
		op[i] = dlsym(handle[i], "op");
		/* if error */
		sym[i] = dlsym(handle[i], "sym");
	}

	for (i = 0; i < sizeof(filename) / sizeof(*filename); i++) {
		for (j = 0; j < sizeof(filename) / sizeof(*filename); j++) {
			if (op[j](op[i](2, 2), 3) == 7) {
				printf("(2 %c 2) %c 3 = 7\n", sym[i](), sym[j]());
			}
		}
	}

	for (i = 0; i < sizeof(filename) / sizeof(*filename); i++) {
		dlclose(handle[i]);
	}

	return 0;
}
