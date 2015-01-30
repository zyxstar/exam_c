#include <stdio.h>


int main(){
    int ch;
    system("stty raw");
    while((ch = getchar()) != 'q')
        putchar(ch);
    system("stty cooked");

}
