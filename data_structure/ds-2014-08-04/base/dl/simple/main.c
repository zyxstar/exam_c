#include <dlfcn.h>

#include <stdio.h>

int main(void)
{
	void *handler;
	int (*funcp)(int, int);

	handler = dlopen("./add.plugin", RTLD_LAZY);
	/* if error */

	funcp = dlsym(handler, "add");
	/* if error */

	printf("%d\n", funcp(123, 456));

	dlclose(handler);

	return 0;
}
