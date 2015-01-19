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

int copy(const char *src, const char *dest){
    int f1, f2, n;
    char buf[BUFSIZE];

    if((f1 = open(src, O_RDONLY, 0)) == -1)
        error("cp: can't open %s", src);
    if((f2 = creat(dest, PERMS)) == -1)
        error("cp: can't create %s, mode %03o", dest, PERMS);
    while((n = read(f1, buf, BUFSIZE)) > 0)
        if(write(f2, buf, n) != n)
            error("cp: write error on file %s", dest);
    close(f1);
    close(f2);
    return 0;
}

int main(int argc, char **argv){
    if(argc != 3)
        error("Usage: cp from to");
    copy(argv[1], argv[2]);
    return 0;
}

// gcc chp8_cp.c -o chp8_cp.out && ./chp8_cp.out
