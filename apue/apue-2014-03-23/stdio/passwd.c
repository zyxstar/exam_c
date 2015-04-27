#include <sys/types.h>
#include <pwd.h>

#include <stdio.h>

#define BUFSIZE 1024

int main(void)
{
	char buf[BUFSIZE];

#if 0
	struct passwd *pwd;
	pwd = getpwuid(500);
	if (pwd == NULL) {
		perror("getpwuid()");
		return 1;
	}
	printf("%s\n", pwd->pw_name);
	printf("%d\n", pwd->pw_uid);
#else
	struct passwd pwd, *result;
	int ret;
	//ret = getpwuid_r(533, &pwd, buf, BUFSIZE, &result);
	ret = getpwuid_r(533, &pwd, buf, 1, &result);
	if (result == NULL) {
		printf("ret = %d\n", ret);
		printf("%s\n", strerror(ret));
		return 0;
	}
	printf("&pwd: %p, result: %p\n", &pwd, result);
	printf("%s\n", pwd.pw_name);
        printf("%d\n", pwd.pw_uid);
#endif

	return 0;
}
