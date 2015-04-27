#include <stdio.h>
#include <string.h>

#define BUFSIZE 64

char *mystrcpy(char *dest, const char *src)
{
#if 1
	char *save = dest;
	while (*dest++ = *src++)
		;
	return save;
#else
	for (; *src != '\0'; dest++, src++) {
		*dest = *src;
	}
	*dest = *src;
#endif
}

char *mystrcat(char *dest, const char *src)
{
	int i, j;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (j = 0; dest[i] = src[j]; i++, j++)
		;

	return dest;
}

int mystrcmp(const char *s1, const char *s2)
{
	for (; *s1 != '\0' && *s1 == *s2; s1++, s2++)
		;

	return *s1 - *s2;
}

int mystrncmp(const char *s1, const char *s2, int n)
{
	int i;

	for (i = 0; i < n && *s1 != '\0' && *s1 == *s2; i++, s1++, s2++)
		;

	if (i == n) {
		return 0;
	}

	return *s1 - *s2;
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

char *mystrncat(char *dest, const char *src, size_t n)
{
	int i;
	char *save = dest;

	for (; *dest != '\0'; dest++)
		;

	for (i = 0; i < n && *src != '\0'; i++, dest++, src++) {
		*dest = *src;
	}
	*dest = '\0';

	return save;
}

int main(void)
{
	char dest[BUFSIZE] = "12345678901234567890";
	char *src = "hello";
	int i;

	dest[3] = '\0';

	//mystrcpy(dest, src);
	//mystrcat(dest, src);
#if 0
	mystrncat(dest, src, 3);
	printf("%s\n", dest);
	for (i = 0; i < 14; i++) {
		printf("%x ", dest[i]);
	}
	printf("\n");
#endif
	//printf("%s\n", mystrcpy(dest, src));

	printf("%d\n", mystrncmp("123", "123", 6));

	return 0;
}
