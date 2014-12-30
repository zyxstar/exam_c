#include "kernel_list.h"
#include "class.h"

typedef struct {
    int year;
    struct list_head class_list;
    struct list_head node;
} GRAGE;


GRADE *grade_new(int year);
void grade_free(GRADE *grade);
int grade_add_class(GRADE *grade, CLASS *cls);
int grade_remove_class(GRADE *grade, CLASS *cls);



