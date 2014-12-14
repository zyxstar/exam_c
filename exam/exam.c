#include <stdio.h>

struct stu
{
    int score;
    char c;
    double d;
    int *p;

};



int main(void){

   struct stu s = {0};
   // printf("%d\n", s1-s2);


   printf("%p\n", s.p);

   return 0;

}




//gcc exam.c -E -o exam.i
//gcc exam.c -o exam.out && ./exam.out

