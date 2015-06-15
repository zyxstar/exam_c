#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define PAGESIZE  22

void print(FILE *, int);
FILE *efopen(char *, char *);
char ttyin();


char *progname;

int main(int argc, char **argv){
    int i, pagesize = PAGESIZE;
    FILE *fp;

    progname = argv[0];
    if(argc > 1 && argv[1][0] == '-'){
        pagesize = atoi(&argv[1][1]);
        argc--;
        argv++;
    }
    if(argc == 1)
        print(stdin, pagesize);
    else
        for(i = 1; i < argc; i++){
            fp = efopen(argv[i], "r");
            print(fp, pagesize);
            fclose(fp);
        }

    return 0;
}

FILE *efopen(char *file, char *mode){
    FILE *fp;
    if((fp = fopen(file, mode)) != NULL)
        return fp;
    fprintf(stderr, "fopen(), %s, %s\n", strerror(errno), file);
    exit(1);
}

void print(FILE *fp, int pagesize){
    static int lines = 0;
    char buf[BUFSIZ];

    while(fgets(buf, sizeof buf, fp) != NULL){
        if(++lines < pagesize)
            fputs(buf, stdout);
        else{
            buf[strlen(buf) - 1] = '\0';
            fputs(buf, stdout);
            fflush(stdout);
            ttyin();
            lines = 0;
        }
    }
}

char ttyin(){
    char buf[BUFSIZ];
    static FILE *tty = NULL;

    if(tty == NULL)
        tty = efopen("/dev/tty", "r");
    while(1){
        if(fgets(buf, BUFSIZ, tty) == NULL || buf[0] == 'q')
            exit(0);
        else if(buf[0] == '!'){
            system(buf + 1);
            printf("!\n");
        }
        else
            return buf[0];

    }
}
