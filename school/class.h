#ifndef CLASS_H_INCLUEDE
#define CLASS_H_INCLUEDE

#include <stdio.h>
#include "kernel_list.h"
#include "student.h"
#include "event.h"


#define CLS_NAMESIZE 32

typedef struct GRADE_TAG GRADE;
typedef struct CLASS_TAG CLASS;

struct CLASS_TAG{
    char name[CLS_NAMESIZE];
    int stu_count;
    struct list_head student_list;
    GRADE *grade;
    struct list_head node;

    EVENT *student_added;
    EVENT *student_deled;
};


CLASS *class_new(char *name);
void class_free(CLASS *);

void class_add_student(CLASS *, STUDENT *);
void class_del_student(CLASS *, STUDENT *);
void class_each_student(CLASS *, void *env, void(*each_do)(STUDENT *, int idx, void *env));

STUDENT *class_find_student_by_id(CLASS *, int id);
STUDENT *class_find_student_by_name(CLASS *, const char *name);

//need free
STUDENT **class_sort_by_score(CLASS *);

void class_save(CLASS *, FILE *);
CLASS *class_load(FILE *);

void class_display(CLASS *, int indent);


#endif
