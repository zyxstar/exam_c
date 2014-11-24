#include <stdio.h>
#include <malloc.h>
#include "filter.h"

int check(int num){return num % 2 == 0;}
int main(){
  int arr[] = {1,2,3,4,5,6};
  int i, count = sizeof(arr) / sizeof(int);
  count = filter(check, arr, count);
  for(i = 0; i < count; i++ ){
    printf("%d\n", arr[i]);
  }
}

// gcc use_with_int.c filter.c -o use_with_int
