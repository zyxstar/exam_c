#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void alrm_handler(int s)
{
	alarm(1);
	puts("Got SIGALRM");
}

int main()
{

	signal(SIGALRM,alrm_handler);
	alarm(1);

	while(1);

	exit(0);
}


