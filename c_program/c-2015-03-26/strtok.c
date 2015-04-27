#include <stdio.h>
#include <string.h>

int main(void)
{
	char *s;

#if 1
	char buf[] = "32167 778 ,,911   ";
	int i;

	for (i = 0; i < sizeof(buf); i++) {
		printf("%x ", buf[i]);
	}
	printf("\n");

	s = strtok(buf, " ,");
	while (s != NULL) {
		printf("%s\n", s);
		s = strtok(NULL, ", ");
	}

	for (i = 0; i < sizeof(buf); i++) {
		printf("%x ", buf[i]);
	}
	printf("\n");
#else
	char buf[] = "avahi:x:70:70:Avahi mDNS/DNS-SD Stack:/var/run/avahi-daemon:/sbin/nologin\n";

	s = strtok(buf, ":\n");
	while (s != NULL) {
		printf("%s\n", s);
		s = strtok(NULL, ":\n");
	}
#endif
	return 0;
}
