#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <fcntl.h>

// #define NAMX_MAX 14

// typedef struct{
//     long ino;
//     char name[NAMX_MAX + 1];
// } Dirent;

// typedef struct{
//     int fd;
//     Dirent d;
// } DIR;

// DIR *opendir(char *dirname);
// Dirent *readdir(DIR *dfd);
// void closedir(DIR *dfd);

void dirwalk(char *, void(*fcn)(char *));

void fsize(char *name){
    struct stat stbuf;
    if(stat(name, &stbuf) == -1){
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }
    if((stbuf.st_mode & S_IFMT) == S_IFDIR)
        dirwalk(name, fsize);
    printf("%ld %d %8ld %s\n", stbuf.st_ino, stbuf.st_mode, stbuf.st_size, name);
}

#define MAX_PATH 1024

void dirwalk(char *dir, void(*fcn)(char *)){
    char name[MAX_PATH];
    struct dirent *dp;
    DIR *dfd;

    if((dfd = opendir(dir)) == NULL){
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }
    while((dp = readdir(dfd)) != NULL){
        if(strcmp(dp->d_name, ".") == 0
           || strcmp(dp->d_name, "..") == 0)
            continue;
        if(strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name))
            fprintf(stderr, "dirwalk: name %s/%s too long\n", dir, dp->d_name);
        else{
            sprintf(name, "%s/%s", dir, dp->d_name);
            fcn(name);
        }
    }
    closedir(dfd);
}


// #define DIRSIZE 14
// struct direct{
//     ino_t d_ino;
//     char d_name[DIRSIZE];
// };

// DIR *opendir(char *dirname){
//     int fd;
//     struct stat stbuf;
//     DIR *dp;

//     if((fd = open(dirname, O_RDONLY, 0)) == -1
//         || fstat(fd, &stbuf) == -1
//         || (stbuf.st_mode & S_IFMT) != S_IFDIR
//         || (dp = (DIR *)malloc(sizeof(DIR))) == NULL)
//         return NULL;
//     dp->fd = fd;
//     return dp;
// }

// void closedir(DIR *dp){
//     if(dp){
//         close(dp->fd);
//         free(dp);
//     }
// }

// Dirent *readdir(DIR *dp){
//     struct direct dirbuf;
//     static Dirent d;
//     while(read(dp->fd, &dirbuf, sizeof(dirbuf)) == sizeof(dirbuf)){
//         if(dirbuf.d_ino == 0) continue;
//         d.ino = dirbuf.d_ino;
//         strncpy(d.name, dirbuf.d_name, DIRSIZE);
//         d.name[DIRSIZE] = '\0';
//         return &d;
//     }
//     return NULL;
// }

int main(int argc, char **argv){
    // fsize("/home/zyx/day01");

    int fd;
    struct direct dirbuf;
    fd = open("/home/zyx/", O_RDONLY, 0);
    printf("%d\n", fd);
    struct stat stbuf;
    fstat(fd, &stbuf);
    printf("%d\n", (stbuf.st_mode & S_IFMT) == S_IFDIR);
    int i, j;
    while(1){
        i = read(fd, (char *)&dirbuf, sizeof(dirbuf));
        printf("%d: %d\n", j++, i);
        if(j == 10) break;
    // printf("%d %c %s %d\n", dirbuf.d_ino, dirbuf.d_type, dirbuf.d_name, sizeof(dirbuf));
    }
    close(fd);
    return 0;
}

// gcc chp8_fsize.c -o chp8_fsize.out && ./chp8_fsize.out
