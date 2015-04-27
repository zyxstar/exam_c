#define _XOPEN_SOURCE
#include <unistd.h>

#include <stdio.h>

int main(void)
{
	char *ptr;
#if 0
	char *dest = "$6$Zb1a0COq$iNxYdfa9/RDFiprczgtRT5yK1XLQQdn2QvxBL9DxcHHcCoR.jcex2uxlrV7LW.z8R8U/wR6MpL/UhhwTkRV2j1";

	ptr = crypt("111", "$6$Zb1a0COq$");
	printf("ptr:  %s\ndest: %s\n", ptr, dest);
#else
	ptr = crypt("abcdefg", "$6$U92aUUCD$");
	printf("ptr: %s\n", ptr);
#endif
	return 0;
}
