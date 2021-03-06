#include <signal.h>
#include <pthread.h>

#include <stdio.h>

static void handler(int signo)
{
	printf("%s %p\n", __func__, (void *)pthread_self());

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
	printf("%s %p\n", __func__, (void *)pthread_self());

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
