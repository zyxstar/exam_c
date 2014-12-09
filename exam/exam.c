#include <stdio.h>


void call(){
    printf("ddd ");
}


typedef int(*FUN)();

int main(void){
   int a=1;
   FUN f = (FUN)call;
   int b=2;
   printf("%d\n",f());

   return 0;

}







//gcc exam.c -E -o exam.i
//gcc exam.c -o exam.out

