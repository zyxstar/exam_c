#include "apue.h"


int main(){
    int maxfd = open_max();
    printf("%d\n", maxfd);
    return 0;
}
