#include <unistd.h>

#include <stdio.h>

int main(void)
{
	printf("before fork\n");
	fflush(NULL);
	fork();
	printf("after fork\n");

	return 0;
}
