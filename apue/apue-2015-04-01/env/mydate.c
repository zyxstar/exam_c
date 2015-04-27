#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>


#define STRSIZE		1024

int main(int argc,char **argv)
{
	time_t stamp;
	struct tm *tm;
	char timestr[STRSIZE];
	char fmt[STRSIZE] = {'\0'};
	int op;	
	FILE *fp = stdout;
	
	stamp = time(NULL);
	tm = localtime(&stamp);	


	while(1)
	{
		op = getopt(argc,argv,"-y:mdH:MS");
		if(op < 0)
			break;
		
		switch(op)
		{
			case 1:
				if(fp == stdout)
				{
					fp = fopen(argv[optind-1],"w");	
					if(fp == NULL)
					{
						perror("fopen()");
						fp = stdout;
					}	
				}
				break;

			case 'y':
				if(strcmp(optarg,"2") == 0)
					strncat(fmt,"%y ",STRSIZE);
				else if(strcmp(optarg,"4") == 0)
						strncat(fmt,"%Y ",STRSIZE);
					 else
						fprintf(stderr,"Invalid argument of -y\n");
				break;

			case 'm':
				strncat(fmt,"%m ",STRSIZE);
				break;

			case 'd':
				strncat(fmt,"%d ",STRSIZE);
				break;

			case 'H':
				if(strcmp(optarg,"12") == 0)
                    strncat(fmt,"%I(%P) ",STRSIZE);
                else if(strcmp(optarg,"24") == 0)
                        strncat(fmt,"%H ",STRSIZE);
                     else
                        fprintf(stderr,"Invalid argument of -H\n");

				break;

			case 'M':
				strncat(fmt,"%M ",STRSIZE);
				break;

			case 'S':
				strncat(fmt,"%S ",STRSIZE);
				break;
	
			default:
				break;
		}
	}

	strncat(fmt,"\n",STRSIZE);
	strftime(timestr,STRSIZE,fmt,tm);
	fputs(timestr,fp);

	if(fp != stdout)
		fclose(fp);

	exit(0);
}


