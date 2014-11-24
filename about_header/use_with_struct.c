#include <stdio.h>
#include "filter.h"

int check(TAG tag){ return tag.score > 60; }
int main(){
  TAG tags[] = {{'a', 61}, {'b', 59}, {'c', 70}};
  int i, count = sizeof(tags) / sizeof(TAG);
  count = filter(check, tags, count);
  for(i = 0; i < count; i++ ){
    printf("%c %d\n", tags[i].name, tags[i].score);
  }
}

// gcc use_with_struct.c filter.c -o use_with_struct
