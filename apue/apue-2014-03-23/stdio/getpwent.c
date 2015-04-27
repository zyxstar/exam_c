#include <sys/types.h>
#include <pwd.h>

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	struct passwd *entry;

	while (1) {
		entry = getpwent();
		if (entry == NULL) {
			break;
		}

		printf("%s:%s:%d:%d\n", entry->pw_name, entry->pw_passwd, entry->pw_uid, entry->pw_gid);
	}

	printf("\n\n");

	setpwent();
	while (1) {
		entry = getpwent();
		if (entry == NULL) {
			break;
		}

		printf("%s:%s:%d:%d\n", entry->pw_name, entry->pw_passwd, entry->pw_uid, entry->pw_gid);
	}

	endpwent();
	return 0;
}
