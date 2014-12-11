#include <stdio.h>
#include <setjmp.h>

#define NEW_EXCPTION(ex) jmp_buf ex;
// #define TRY(ex) do{ if( !setjmp(ex) ){
// #define CATCH } else {
// #define ETRY } }while(0)
// #define THROW(ex) longjmp(ex, 1)


#define TRY(ex) do{switch( setjmp(ex) ){ case 0: while(1){
#define CATCH(no) break; case no:
#define FINALLY break; } default:
#define ETRY } }while(0)
#define THROW(ex,no) longjmp(ex, no)


#define FOO_EXCEPTION (1)
// #define BAR_EXCEPTION (2)
// #define BAZ_EXCEPTION (3)



NEW_EXCPTION(myex);

double divide(double to, double by)
{
      if(by == 0)
        THROW(myex,FOO_EXCEPTION);
      return to / by;
}

void f()
{
   TRY(myex)
   {
      printf("%f\n", divide(2, 0));
   }
   CATCH(FOO_EXCEPTION)
   {
      printf("Got Exception!\n");
   }
   FINALLY
   {
      printf("...et in arcadia Ego\n");
   }
   ETRY;
}

int main(void){
   f();

   return 0;

}



   // do{
   //    jmp_buf ex_buf__;
   //    if( !_setjmp (ex_buf__) ){
   //        if(by == 0)
   //          longjmp(ex_buf__, 1);
   //        return to / by;
   //    }
   //    else{
   //        printf("Got Exception!\n");
   //    }
   //  }while(0);



//gcc exam.c -E -o exam.i
//gcc exam.c -o exam.out && ./exam.out

