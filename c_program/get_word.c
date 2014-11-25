#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int get_word(char *buf, int buf_size, FILE *fp){
    int len;
    char ch;

    while((ch = getc(fp)) != EOF && !isalnum(ch))
        ;

    if(ch==EOF) return EOF;

    len = 0;
    do{
        buf[len] = ch;
        len++;
        if(len >= buf_size){
            fprintf(stderr, "word too long.\n");
            exit(1);
        }
    } while((ch = getc(fp)) != EOF && isalnum(ch));

    buf[len] = '\0';
    return len;
}

int main(int argc, const char* argv[]){
    char buf[256];
    while(get_word(buf, 256, stdin) != EOF){
        printf("<<%s>>\n", buf);
    }

    return 0;
}
