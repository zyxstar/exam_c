#include <sys/select.h>

#include <stdio.h>

/* ./a.out second */
int main(int argc, char **argv)
{
	int sec;
	struct timeval tv;

	if (argc != 2) {
		fprintf(stderr, "argment...\n");
		return 1;
	}

	sec = atoi(argv[1]);
	printf("before sleep\n");

	//sleep(sec);
	tv.tv_sec = sec;
	tv.tv_usec = 0;
	select(0, NULL, NULL, NULL, &tv);

	printf("after sleep\n");

	return 0;
}
