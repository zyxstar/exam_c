#include "utils.h"
#include <stdio.h>    // for printf()






// #include <stdio.h>    // for printf()
// #include <signal.h>
// #include <sys/time.h>

// #include <errno.h>








// void sigFunc()
// {
//    static int iCnt = 0;
//    printf("The %d Times: Hello world\n", iCnt++);
// }

// int main(void)
// {
//    struct itimerval tv, otv;
//    signal(SIGALRM, sigFunc);
//    //how long to run the first time
//    tv.it_value.tv_sec = 1;
//    tv.it_value.tv_usec = 0;
//    //after the first time, how long to run next time
//    tv.it_interval.tv_sec = 0;
//    tv.it_interval.tv_usec = 999999;

//    if (setitimer(ITIMER_REAL, &tv, &otv) != 0)
//     printf("setitimer err %d\n", errno);

//    while(1)
//    {
//     // sleep(1);
//     // printf("otv: %d, %d, %d, %d\n", otv.it_value.tv_sec, otv.it_value.tv_usec, otv.it_interval.tv_sec, otv.it_interval.tv_sec);
//    }
// }


// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <signal.h>
// #include <time.h>
// #include <sys/time.h>


// int sec;
// void sigroutine(int signo){
//     switch (signo){
//         case SIGALRM:
//             printf("Catch a signal -- SIGALRM \n");
//             signal(SIGALRM, sigroutine);
//             break;
//         case SIGVTALRM:
//             printf("Catch a signal -- SIGVTALRM \n");
//             signal(SIGVTALRM, sigroutine);
//             break;
//     }
//     return;
// }
// int main()
// {
//     struct itimerval value, ovalue, value2;          //(1)
//     sec = 5;
//     printf("process id is %d\n", getpid());
//     signal(SIGALRM, sigroutine);
//     // signal(SIGVTALRM, sigroutine);


//     value.it_value.tv_sec = 0;
//     value.it_value.tv_usec = 500000;

//     value.it_interval.tv_sec = 0;
//     value.it_interval.tv_usec = 1000000;

//     setitimer(ITIMER_REAL, &value, &ovalue);    //(2)


//     // value2.it_value.tv_sec = 0;
//     // value2.it_value.tv_usec = 500000;
//     // value2.it_interval.tv_sec = 0;
//     // value2.it_interval.tv_usec = 500000;
//     // setitimer(ITIMER_VIRTUAL, &value2, &ovalue);
//     for(;;)
//         ;
// }

int count =0;
SIMPER_TIMER timer1;

void handler(void *env){

    printf("hello world%d\n", *((int*)env));
}


void handler2(){
    count++;
    if (count==5) timer_destroy(&timer1);
    printf("tick %d\n", count);
}

#define itoc(arg) ##arg

int main(){
    int data = 999;
    void *env = &data;

    timer_new(&timer1, 3000, handler, env);
    timer_start(&timer1);

    SIMPER_TIMER timer2;
    timer_new(&timer2, 1000, handler2, env);
    timer_start(&timer2);

    printf("%s\n", itoc(__LINE__));

    while(1);

    return 0;
}





// gcc  timer.c  -o timer.out && ./timer.out


// gcc -I ../utils ../utils/utils.c timer.c -DDEBUG -o timer.out && ./timer.out
