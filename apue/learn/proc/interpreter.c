#include <unistd.h>

#include <stdio.h>

int main(void)
{
	execl("./cmdline.sh", "aaa", "bbb", "ccc", NULL);
	perror("./cmdline.sh");
	return 1;
}
