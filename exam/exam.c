#include <stdio.h>


struct stu
{
    int score;
};

void call(){
    printf("ddd ");
}


typedef int(*FUN)();

int main(void){
   struct stu s1={10};
   struct stu s2={10};
   // printf("%d\n", s1-s2);

   char *name = "abcd";

   printf("%c\n", *name);

   return 0;

}







//gcc exam.c -E -o exam.i
//gcc exam.c -o exam.out && ./exam.out

