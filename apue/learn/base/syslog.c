#include <syslog.h>

int main(void)
{
	//syslog(LOG_ERR | LOG_DAEMON, "%s: hello log\n", __FILE__);
	syslog(LOG_EMERG, "%s: hello log\n", __FILE__);

	closelog();

	return 0;
}
