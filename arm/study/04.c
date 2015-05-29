#include <stdio.h>

void myswap(int *a, int *b){
    int c = *a;
    *a = *b;
    *b = c;
}


int main(void){
    int a = 12;
    int b = 34;
    myswap(&a, &b);
    return 0;
}
