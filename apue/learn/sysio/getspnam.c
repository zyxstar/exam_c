#include <shadow.h>

#include <stdio.h>

int main(void)
{
	struct spwd *sp;

	sp = getspnam("hsienmu");
	if (sp == NULL) {
		perror("hsienmu");
		return 1;
	}

	printf("%s, %s\n", sp->sp_namp, sp->sp_pwdp);

	return 0;
}
