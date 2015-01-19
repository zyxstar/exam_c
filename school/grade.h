#ifndef GRADE_H_INCLUEDE
#define GRADE_H_INCLUEDE

#include <stdio.h>
#include <kernel_list.h>
#include "class.h"

typedef struct GRADE_TAG GRADE;

struct GRADE_TAG{
    int year;
    struct list_head class_list;
    struct list_head node;
    int cls_count;
    int stu_count;
};


GRADE *grade_new(int year);
void grade_free(GRADE *);

void grade_add_class(GRADE *, CLASS *);
void grade_del_class(GRADE *, CLASS *);

void grade_each_class(GRADE *, void *env, void(*each_do)(CLASS *, int idx, void *env));

CLASS *grade_find_class_by_name(GRADE *, const char *name);
STUDENT ** grade_sort_by_score(GRADE *);

void grade_save(GRADE *, FILE *);
GRADE *grade_load(FILE *);

void grade_display(GRADE *, int indent);

#endif
