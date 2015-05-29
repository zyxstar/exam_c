#include <stdio.h>

void mycall(){}

void myloop(){
    int i;
    for(i = 0; i < 10; i++)
        mycall();
}


int main(void){
    myloop();
    return 0;
}
