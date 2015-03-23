#include <pthread.h>

#include <stdio.h>
#include <errno.h>

int main(void)
{
	printf("%d\n", errno);
}

1 -------->alarm 20--------------------->
2 ---------------->---5s-->alarm 6------>
3
