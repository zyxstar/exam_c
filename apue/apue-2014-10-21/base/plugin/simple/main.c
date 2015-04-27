#include <dlfcn.h>

#include <stdio.h>

int main(void)
{
	int a, b, c;
	int (*funcp)(int, int);
	void *handle;

	handle = dlopen("./add.plugin", RTLD_LAZY);
	if (handle == NULL) {
		fprintf(stderr, "./add.plugin err\n");
		return 1;
	}

	funcp = dlsym(handle, "add");
	if (funcp == NULL) {
		fprintf(stderr, "dlsym() err\n");
		dlclose(handle);
		return 1;
	}

	a = 3, b = 8;
	c = funcp(a, b);
	printf("c = %d\n", c);

	dlclose(handle);

	return 0;
}
