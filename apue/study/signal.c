#include <signal.h>

#include <stdio.h>

static void handler(int signo)
{
	if (signo == SIGINT) {
		printf("Catch SIGINT\n");
	} else if (signo == SIGQUIT) {
		printf("Catch SIGQUIT\n");
	} else {
		printf("error\n");
	}
}

int main(void)
{
	int i;
	void (*save)(int);

	save = signal(SIGINT, handler);
	signal(SIGQUIT, handler);

	// for (i = 0; ; i++) {
	// 	if (i == 10) {
	// 		signal(SIGINT, save);
	// 	}
		pause();
	// }

	return 0;
}
