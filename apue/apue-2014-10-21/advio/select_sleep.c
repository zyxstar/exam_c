#include <sys/select.h>

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int i;
	struct timeval tval;

	for (i = 0; ; i++) {
#if 0
		sleep(3);
#else
		tval.tv_sec = 3;
		tval.tv_usec = 0;
		select(0, NULL, NULL, NULL, &tval);
#endif
		printf("i = %d\n", i);
	}

	return 0;
}
