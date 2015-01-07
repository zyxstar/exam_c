#ifndef ARRAY_H_INCLUEDE
#define ARRAY_H_INCLUEDE

#include <stdlib.h>
#include <string.h>


#define arr_len(arr) ((sizeof(arr)) / (sizeof(*arr)))

#define _for_each(idx, length)\
    int idx;\
    for(idx = 0; idx < length; idx++)

#define _malloc_with_type(elem_type, len)\
    malloc(sizeof(elem_type) * (len))



#define def_reduce(fun_name, elem_type, acc_type)\
    void fun_name(void(*callback)(acc_type *, elem_type *, int), elem_type *elem_arr, int arr_size, acc_type  *stat){\
        _for_each(idx, arr_size){\
            callback(stat, &(elem_arr[idx]), idx);\
        }\
    }

#define def_each(fun_name, elem_type)\
    void fun_name(void(*callback)(elem_type*, int), elem_type *elem_arr, int arr_size){\
        _for_each(idx, arr_size){\
            callback(&(elem_arr[idx]), idx);\
        }\
    }

//need free
#define def_map(fun_name, src_type, dest_type)\
    dest_type* fun_name(void(*callback)(src_type*, dest_type*, int), src_type *src_arr, int arr_size){\
        dest_type* ret = _malloc_with_type(dest_type, arr_size);\
        _for_each(idx, arr_size){\
            callback(&src_arr[idx], &ret[idx], idx);\
        }\
        return ret;\
    }

//need free
#define def_filter(fun_name, elem_type)\
    elem_type** fun_name(int(*predicate)(elem_type*, int), elem_type *elem_arr, int arr_size, int *found_count){\
        *found_count = 0;\
        elem_type **ret = _malloc_with_type(elem_type *, arr_size);\
        _for_each(idx, arr_size){\
            if(predicate(&elem_arr[idx], idx)){\
                ret[*found_count] = &elem_arr[idx];\
                (*found_count)++;\
            }\
        }\
        return ret;\
    }



int range(int start, int end, int step, int* arr){
    if(step == 0) return 0;
    if(step > 0 && end < start) return 0;
    if(step < 0 && start < end) return 0;
    int new_size = 0;
    while(1){
        if(step > 0 && start >= end) break;
        if(step < 0 && start <= end) break;
        arr[new_size++] = start;
        start += step;
    }
    return new_size;
}


#endif
