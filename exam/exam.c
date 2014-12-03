#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <string.h>

static struct termios stored_settings1;
static struct termios stored_settings2;

void echo_off(void)
{
   struct termios new_settings;
   tcgetattr(0,&stored_settings1);
   new_settings =stored_settings1;
   new_settings.c_lflag &= (~ECHO);
   tcsetattr(0,TCSANOW,&new_settings);
   return;

}

void echo_on(void)
{
  tcsetattr(0,TCSANOW,&stored_settings1);
  return;
}

void set_keypress(void)
{
  struct termios new_settings;
  tcgetattr(0,&stored_settings2);
  new_settings = stored_settings2;

  /*Disable canornical mode, and set buffer size to 1 byte */
  new_settings.c_lflag&=(~ICANON);
  new_settings.c_cc[VTIME] = 0;
  new_settings.c_cc[VMIN] = 1;

  tcsetattr(0, TCSANOW, &new_settings);
  return;

}
void reset_keypress(void)
{
  tcsetattr(0, TCSANOW, &stored_settings2);
  return;
}
int main()
{

  printf("========================\n");
  printf("0. Main menu\n");
  printf("1. Chapter one\n");
  printf("2. Chapter two\n");
  printf("3. Chapter three\n");
  printf("========================\033[?25h\n");
  echo_off();
  set_keypress();
  char ch;
  while((ch = getchar() ) != 'q')
  {
    switch(ch)
    {
      case '0':
        printf("In main menu.\n");break;
      case '1':
        printf("Entering chapter one\n");break;
      case '2':
        printf("Entering chapter two\n");break;
      case '3':
        printf("Entering chapter three\n");break;
      default:
        printf("Entering other chapter.\n");
     }
   }
  reset_keypress();
  echo_on();
  return 0;

}

//gcc exam.c -o exam.out && ./exam.out
