
#include <stdio.h>

void sort_bubble(int *arr, int size){
    int i, j, temp, flag;
    for(i = 0; i < size - 1; i++){
        flag = 0;
        for(j = 0; j < size - i - 1; j++){
            if(arr[j] > arr[j + 1]){
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] =  temp;
                flag = 1;
            }
        }
        if(flag == 0) break; // if already ordered
    }
}

void sort_selection(int *arr, int size){
    int i, j, min_idx, temp;
    for(i = 0; i < size; i++){
        min_idx = i;
        for(j = i + 1; j < size; j++){
            if(arr[j] < arr[min_idx]){
                min_idx = j;
            }
        }
        if(min_idx != i){
            temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

static int _find_idx(int *arr, int idx){
    int i;
    for(i = 0; i < idx; i++)
        if(arr[i] > arr[idx]) break;
    return i;
}

static void _move(int *arr, int begin, int end){
    int i;
    for(i = end; i > begin; i--)
        arr[i] = arr[i-1];
}

void sort_insert(int *arr, int size){
    int i, pos, temp;
    for(i = 1; i < size; i++){
        if(arr[i] < arr[i - 1]){ // if not order
            pos = _find_idx(arr, i);
            if(i != pos){
                temp = arr[i];
                _move(arr, pos, i);
                arr[pos] = temp;
            }
        }
    }
}



#define test_sort(sort_fn)\
    printf("----------------\n%s:\n", #sort_fn);\
    _test_sort(sort_fn);

void _test_sort(void(*sort_fn)(int *, int )){
    int arr[] = {10, 8, 17, 4, 20, 17, 22, 3};
    sort_fn(arr, sizeof(arr) / sizeof(int));
    int i;
    for(i = 0; i < size; i++)
        printf("%d ", arr[i]);    
    printf("\n");
}

int main(){
    test_sort(sort_bubble);
    test_sort(sort_selection);
    test_sort(sort_insert);

    return 0;
}


// gcc sort.c -o sort.out && ./sort.out 
