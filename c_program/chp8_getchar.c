#include <stdio.h>
#include <unistd.h>

int getchar1(void){
    char c;
    return (read(0, &c, 1) == 1) ? (unsigned char) c : EOF;
}

#define BUFSIZE 1024

int getchar2(void){
    static char buf[BUFSIZE];
    static char *bufp = buf;
    static int n = 0;

    if(n == 0){
        n = read(0, buf, sizeof buf);
        bufp = buf;
    }
    return (--n >= 0) ? (unsigned char) *bufp++ : EOF;
}

int main(){
    int c;
    c = getchar1();
    printf("%c\n", c);

    c = getchar2();
    printf("%c\n", c);
    return 0;
}

// gcc chp8_getchar.c -o chp8_getchar.out && ./chp8_getchar.out
