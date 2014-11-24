#include "mytype.h"

#ifndef FILTER_H_INCLUEDE
#  define FILTER_H_INCLUEDE

int filter(int(*predicate)(FILTER_ELEM), FILTER_ELEM *arr, int size);

#endif /*FILTER_H_INCLUEDE*/
