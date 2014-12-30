#ifndef CLASS_H_INCLUEDE
#define CLASS_H_INCLUEDE

#include <stdio.h>
#include "kernel_list.h"
#include "student.h"

#define CLS_NAMESIZE 32


typedef struct {
    char name[CLS_NAMESIZE];
    struct list_head student_list;
    struct list_head node;
} CLASS;

typedef int CMP_FN(const STUDENT *, const STUDENT *);
typedef void EACH_DO_FN(STUDENT *, int idx, void *env);



CLASS *class_new(char *name);
void class_free(CLASS *cls);

void class_add_student(CLASS *cls, STUDENT *stu);
void class_del_student(CLASS *cls, STUDENT *stu);
void class_each_student(CLASS *cls, void *env, EACH_DO_FN *);
STUDENT *class_find_student_by_id(CLASS *cls, int id);
STUDENT *class_find_student_by_name(CLASS *cls, const char *name);
void class_sort(CLASS *cls, CMP_FN *);

void class_save(CLASS *cls, FILE *fp);
CLASS *class_load(FILE *fp);

void class_display(CLASS *cls, int indent);
#endif
