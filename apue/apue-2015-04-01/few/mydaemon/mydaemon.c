#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>
#include <errno.h>

#define FNAME		"/tmp/out"

static int daemonize(void)
{
	pid_t pid;	
	int fd;

	pid = fork();
	if(pid < 0)
//		syslog(LOG_ERR,"fork():%s",strerror(errno));
		return -1;	
	
	if(pid > 0)
		exit(0);

	fd = open("/dev/null",O_RDWR);
	if(fd < 0)
		return -2;
			
	dup2(fd,0);	
	dup2(fd,1);	
	dup2(fd,2);	

	if(fd > 2)
		close(fd);

	setsid();
	
	chdir("/");
	umask(0);

	return 0;

}

int main()
{
	FILE *fp;
	int i;

	openlog("mydaemon",LOG_PID,LOG_DAEMON);

	if(daemonize())
	{
		syslog(LOG_ERR,"daemonize() failed.");
		exit(1);
	}	
	else
	{
		syslog(LOG_INFO,"daemonize() successed.");
	}

	fp = fopen(FNAME,"w");
	if(fp == NULL)
	{
		syslog(LOG_ERR,"fopen():%s",strerror(errno));
		exit(1);
	}
	
	for(i = 0 ; ; i++)
	{
		fprintf(fp,"%d\n",i);
		fflush(fp);
		syslog(LOG_DEBUG,"%d was printed.",i);
		sleep(1);
	}

	fclose(fp);
	closelog();

	exit(0);
}


