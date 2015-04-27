#include <stdio.h>
#include <string.h>

char *mystrcpy(char *dest, const char *src)
{
	char *save = dest;
#if 0
	while (*src != '\0') {
		*dest = *src;
		dest++, src++;
	}
	*dest = '\0';
#else
	while ((*dest++ = *src++))
		;
#endif
	return save;
}

char *mystrcat(char *dest, const char *src)
{
	int i, j;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (j = 0; src[j] != '\0'; j++, i++) {
		dest[i] = src[j];
	}
	dest[i] = '\0';

	return dest;
}

int mystrcmp(const char *s1, const char *s2)
{
	int i;

	for (i = 0; s1[i] != '\0'; i++) {
		if (s1[i] != s2[i]) {
			break;
		}
	}

	return s1[i] - s2[i];
}

int main(void)
{
	char dest[36] = "hello";
	char *src = "hello";

	//mystrcat(dest, src);
	//printf("%s\n", dest);
	printf("%d\n", mystrcmp(dest, src));

	return 0;
}
