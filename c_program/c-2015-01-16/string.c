#include <stdio.h>
#include <string.h>

char *mystrcpy(char *dest, const char *src)
{
	char *save = dest;

#if 0
	while (*src != '\0') {
		*dest = *src;
		dest++; src++;
	}
	*dest = '\0';

	return save;
#endif
	while ((*dest++ = *src++))
		;

	return save;
}

char *mystrncpy(char *dest, const char *src, size_t n)
{
	int i;

	for (i = 0; i < n && src[i] != '\0'; i++) {
		dest[i] = src[i];
	}

	for (; i < n; i++) {
		dest[i] = '\0';
	}

	return dest;
}

char *mystrcat(char *dest, const char *src)
{
	char *save = dest;

	while (*dest) {
		dest++;
	}

	while ((*dest++ = *src++))
		;

	return save;
}

char *mystrncat(char *dest, const char *src, size_t n)
{
	char *save = dest;
	int i;

	while (*dest) {
		dest++;
	}

	for (i = 0; i < n && src[i] != '\0'; i++) {
		dest[i] = src[i];
	}
	dest[i] = '\0';

	return save;
}

int mystrcmp(const char *s1, const char *s2)
{
	int i;

	for (i = 0; s1[i] != '\0' && s1[i] == s2[i]; i++)
		;

	return s1[i] - s2[i];
}

int main(void)
{
	char dest[128] = "123456789";
	char *src = "1234";

	//mystrcpy(dest, src);
	//printf("%s\n", dest);

	//mystrncat(dest, src, 27);
	//printf("%s\n", dest);

	printf("%d\n", mystrcmp(dest, src));

	return 0;
}
