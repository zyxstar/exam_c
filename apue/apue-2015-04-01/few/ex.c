#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*date +%s*/


int main()
{

	puts("Begin!");

	fflush(NULL);

	execl("/bin/date","date","+%s",NULL);

	puts("End!");

	exit(0);
}



