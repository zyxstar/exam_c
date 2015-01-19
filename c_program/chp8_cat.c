#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



#define PERMS 0666
#define BUFSIZE 1024

void error(char *fmt, ...){
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}

void copy(int ifd, int ofd){
    int n;
    char buf[BUFSIZE];

    while((n = read(ifd, buf, BUFSIZE)) > 0)
        if(write(ofd, buf, n) != n)
            error("cat: write error");
}

int main(int argc, char **argv){
    int fd;

    if(argc == 1)
        copy(0, 1);
    else
        while(--argc > 0)
            if((fd = open(*++argv, O_RDONLY)) == -1)
                error("cat: can't open %s", *argv);
            else{
                copy(fd, 1);
                close(fd);
            }
    return 0;
}

// gcc chp8_cat.c -o chp8_cat.out && ./chp8_cat.out
