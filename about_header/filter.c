#include "filter.h"

int filter(int(*predicate)(FILTER_ELEM), FILTER_ELEM *arr, int size){
    int i, new_size = 0;
    FILTER_ELEM temp;
    for(i = 0; i < size; i++){
        if(predicate(arr[i])){
            temp = arr[i];
            arr[new_size] = temp;
            new_size++;
        }
    }
    return new_size;
}
