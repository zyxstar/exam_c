#include <stdio.h>
#include <stdlib.h>
#include "utils.h"




int main(int argc, const char* argv[]){

  init_frame();
  return 0;
}


// gcc -I ../utils ../utils/utils.c tetris.c view.c app.c -o app.out -DDEBUG && ./app.out
// gcc -I ../utils ../utils/utils.c tetris.c view.c app.c -o app.out && ./app.out
