#ifndef CLASS_H_INCLUEDE
#define CLASS_H_INCLUEDE

#include "list.h"
#include "student.h"

#define CLS_NAMESIZE 32


typedef struct {
    char name[CLS_NAMESIZE];
    struct list_head student_list;
    struct list_head node;
} CLASS;

// typedef int cmp_fn(const void *, const STUDENT *);

CLASS *class_new(char *name);
void class_free(CLASS *cls);

void class_add_student(CLASS *cls, STUDENT *stu);
void class_del_student(CLASS *cls, STUDENT *stu);
void class_each_student(CLASS *cls, void *env, void(*each_do_fn)(STUDENT *, void *));

STUDENT *class_find_student_by_id(CLASS *cls, int id);
STUDENT *class_find_student_by_name(CLASS *cls, const char *name);

void class_display(CLASS *cls, int indent);
// void class_sort(CLASS *cls, cmp_fn *);

#endif
