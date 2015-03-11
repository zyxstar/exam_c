#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

int main()
{

    int in = 0;
    int j;
    char buffer[] = "Fred male 25,John male 62,Anna female 16";
    char *p[20];
    char *buf = buffer;
    char *outer_ptr = NULL;
    char *inner_ptr = NULL;
    while ((p[in] = strtok_r(buf, ",", &outer_ptr)) != NULL)
    {
        buf = p[in];
        while ((p[in] = strtok_r(buf, " ", &inner_ptr)) != NULL)
        {
            in++;
            buf = NULL;
        }
        buf = NULL;
    }
    printf("Here we have %d strings/n", in);
    for (j = 0; j < in; j++)
    {
        printf(">%s<\n", p[j]);
    }

    return 0;
}


#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>

int system(const char *cmdstring){   /* version without signal handling */
    pid_t   pid;
    int     status;

    if (cmdstring == NULL)
        return (1);             /* always a command processor with UNIX */
    if ((pid = fork()) < 0)
        status = -1;            /* probably out of processes */
    else if (pid == 0) {                         /* child */
        execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
        _exit(127);             /* execl error */
    }
    else {                      /* parent */
        while (waitpid(pid, &status, 0) < 0){
            if (errno != EINTR){
                status = -1;    /* error other than EINTR from waitpid() */
                break;
            }
        }
    }

    return (status);
}
