#include <dlfcn.h>

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int (*funcp)(int, int);
	void *ptr;

	ptr = dlopen("./add.plugin", RTLD_LAZY);
	if (ptr == NULL) {
		fprintf(stderr, "dlopen() failed.\n");
		return 1;
	}

	funcp = dlsym(ptr, "add");
	printf("%d\n", funcp(333, 66));

	dlclose(ptr);

	return 0;
}
