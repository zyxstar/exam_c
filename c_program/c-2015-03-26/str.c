#include <stdio.h>

int main(void)
{
	char str[8] = {'a', 'b', 'c', '\0'};
	char str1[8] = "abc";
	char *s = "abc";

	str[1] = 'A';
	printf("%s\n", str);

	s[1] = 'A';
	printf("%s\n", s);

	return 0;
}
