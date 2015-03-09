#include <sys/types.h>
#include <pwd.h>

#include <stdio.h>

int main(void)
{
	struct passwd *pwd;

	pwd = getpwuid(500);
	if (pwd == NULL) {
		perror("getpwuid()");
		return 1;
	}

	printf("%s %s %d %d %s %s %s\n", pwd->pw_name, pwd->pw_passwd, pwd->pw_uid, pwd->pw_gid, pwd->pw_gecos, pwd->pw_dir, pwd->pw_shell);

	return 0;
}
