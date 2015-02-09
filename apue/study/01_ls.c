#include "apue.h"
#include <dirent.h>

int main(int argc, char **argv){
    DIR *dp;
    struct dirent *dirp;

    if(argc != 2)
        err_quit("usage: ls dir name");

    if((dp = opendir(argv[1])) == NULL)
        err_sys("can't open %s", argv[1]);

    while((dirp = readdir(dp)))
    return 0;
}

// gcc ./lib/error.o 01_ls.c -o 01_ls.out
