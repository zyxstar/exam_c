#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define NAMX_MAX 14

typedef struct{
    long ino;
    char name[NAMX_MAX + 1];
} Dirent;

typedef struct{
    int fd;
    Dirent d;
} DIR;

DIR *opendir(char *dirname);
Dirent *readdir(DIR *dfd);
void closedir(DIR *dfd);



int main(int argc, char **argv){
    FILE *fp = fopen("/etc/passwd", "r");

    int ch;
    while((ch = getc(fp)) != EOF)
        putchar(ch);

    fflush(stdout);
    fclose(fp);
    return 0;
}

// gcc chp8_fsize.c -o chp8_fsize.out && ./chp8_fsize.out
