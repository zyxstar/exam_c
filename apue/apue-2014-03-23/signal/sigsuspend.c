#include <signal.h>

#include <stdio.h>

void handler(int unuse)
{
	printf("call %s()\n", __func__);
}

int main(void)
{
	sigset_t bset, unbset, oset, saveset;

	signal(SIGINT, handler);

	sigemptyset(&bset);
	sigaddset(&bset, SIGINT);

	sigprocmask(SIG_UNBLOCK, &bset, &oset);
	sigprocmask(SIG_BLOCK, &bset, &unbset);

	/* op 1 */

	while (1) {
#if 0
		sigprocmask(SIG_SETMASK, &unbset, &saveset);
		pause();
		sigprocmask(SIG_SETMASK, &saveset, NULL);
#else
		sigsuspend(&unbset);
#endif

		printf("in while\n");
	}
	sigprocmask(SIG_SETMASK, &oset, NULL);

	return 0;
}
