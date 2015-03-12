#include <stdio.h>
#include <unistd.h>

int main(){
    if(isatty(STDOUT_FILENO))
        printf("terminal\n");
    else
        printf("redirect\n");
    return 0;
}
