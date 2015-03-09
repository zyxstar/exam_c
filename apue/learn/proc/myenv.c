#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main(void)
{
	char *p;

	p = getenv("LANG");
	printf("%s\n", p);

#if 0
	putenv("LANG=xxxxxxxxxxxxxx");
#else
	//setenv("LANG", "1234567890", 0);
	setenv("LANG", "1234567890", 1);
#endif

	p = getenv("LANG");
	printf("%s\n", p);

#if 0
	char **p;

	for (p = environ; *p != NULL; p++) {
		printf("%s\n", *p);
	}
#endif
	return 0;
}
