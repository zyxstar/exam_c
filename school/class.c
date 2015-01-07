#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kernel_list.h"
#include "kernel_list_helper.h"
#include "student.h"
#include "class.h"
#include "grade.h"



CLASS *class_new(char *name){
    CLASS *cls = malloc(sizeof(*cls));
    INIT_LIST_HEAD(&cls->student_list);
    strncpy(cls->name, name, CLS_NAMESIZE);
    cls->stu_count = 0;
    cls->grade = NULL;
    return cls;
}

static void _student_free(STUDENT *stu, int idx, void *env){
    student_free(stu);
}

void class_free(CLASS *cls){
    class_each_student(cls, NULL, _student_free);
    free(cls);
}

void class_add_student(CLASS *cls, STUDENT *stu){
    list_add_tail(&stu->node, &cls->student_list);
    stu->cls = cls;
    cls->stu_count++;
}

void class_del_student(CLASS *cls, STUDENT *stu){
    __list_del_entry(&stu->node);
    student_free(stu);
    cls->stu_count--;
}

// declare
void class_each_student(CLASS *, void *env, void(*each_do)(STUDENT *, int idx, void *env));
// implement
_implement_list_each(class_each_student, CLASS, student_list, STUDENT, node);



// declare
STUDENT *_class_find_student(CLASS *, const void *key, int(*cmp)(const void *key, const STUDENT *));
// implement
_implement_list_find(_class_find_student, CLASS, student_list, STUDENT, node);

static _id_cmp(const void *key, const STUDENT *stu){
    const int *id = key;
    return stu->id - *id;
}

STUDENT *class_find_student_by_id(CLASS *cls, int id){
    return _class_find_student(cls, &id, _id_cmp);
}

static _name_cmp(const void *key, const STUDENT *stu){
    const char *name = key;
    return strcmp(stu->name, name);
}

STUDENT *class_find_student_by_name(CLASS *cls, const char *name){
    return _class_find_student(cls, name, _name_cmp);
}




static void _append_to_arr(STUDENT *stu, int idx, void *env){
    STUDENT **arr = env;
    arr[idx] = stu;
}

STUDENT **class_sort_by_score(CLASS *cls){
    STUDENT **arr = malloc(sizeof(STUDENT *) * cls->stu_count);
    class_each_student(cls, arr, _append_to_arr);
    return student_sort(arr, student_cmp_by_score, cls->stu_count);
}





// declare
void _class_save(CLASS *, FILE *, void(*save_entry)(STUDENT *, FILE *));
// implement
_implement_list_save(_class_save, CLASS, student_list, STUDENT, node);


void class_save(CLASS *cls, FILE *fp){
    cls->stu_count = 0; // need'nt write to file
    _class_save(cls, fp, student_save);
}



// declare
CLASS *_class_load(FILE *, void(*load_entry)(CLASS *, FILE *));
// implement
_implement_list_load(_class_load, CLASS, student_list);

static void _student_load_to_class(CLASS *cls, FILE *fp){
    class_add_student(cls, student_load(fp));
}

CLASS *class_load(FILE *fp){
    return _class_load(fp, _student_load_to_class);
}



static void _student_display(STUDENT *stu, int idx, void *env){
    int *indent = env;
    student_display(stu, *indent + 2);
}

void class_display(CLASS *cls, int indent){
    char format[] = "%0sCLASS: [grade(year)]%04d\t[name]%s\t[stu_count]%d\n";
    format[1] = '0' + (indent > 9 ? 9 : indent);
    printf(format, "", (cls->grade == NULL) ? 0 : cls->grade->year, cls->name, cls->stu_count);
    class_each_student(cls, &indent, _student_display);
}


