#include <stdio.h>
#include <string.h>

int main(void)
{
	char dest[32] = "123456789";
	char *src = "abcde";

	//strcpy(dest, src);
	//strcat(dest, src);
	strcmp(dest, src);

	printf("%s\n", dest);

	return 0;
}
