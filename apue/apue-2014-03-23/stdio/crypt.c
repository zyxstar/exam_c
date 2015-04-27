#define _XOPEN_SOURCE
#include <unistd.h>

#include <stdio.h>

int main(void)
{
	char *s;

	s = crypt("111", "$6$q8VEGNew$");
	printf("%s\n", s);
	printf("%s\n", "$6$q8VEGNew$KobqAO9EJWSAwOugsQLJnpKfIm/Id1NzYVm8yS4W3hE.JQXbx.JcgsbDLK04.0oQS8mLKFhsOyDzWWjYNb3HA/");

	return 0;
}
