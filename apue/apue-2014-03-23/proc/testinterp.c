#include <unistd.h>

#include <stdio.h>

int main(void)
{
	execl("./xxx.sh", "./xxx.sh", "aaa", "bbb", NULL);
	perror("execl()");

	return 1;
}
