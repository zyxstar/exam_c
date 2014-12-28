#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "class.h"
#include "student.h"


CLASS *class_new(char *name){
    CLASS *cls = malloc(sizeof(*cls));
    strncpy(cls->name, name, CLS_NAMESIZE);
    INIT_LIST_HEAD(&cls->student_list);
    return cls;
}

static void _student_free(STUDENT *stu, void *env){
    student_free(stu);
}

void class_free(CLASS *cls){
    class_each_student(cls, NULL, _student_free);
    free(cls);
}

void class_add_student(CLASS *cls, STUDENT *stu){
    list_add_tail(&stu->node, &cls->student_list);
}

void class_del_student(CLASS *cls, STUDENT *stu){
    __list_del_entry(&stu->node);
    student_free(stu);
}

void class_each_student(CLASS *cls, void *env, void(*each_do_fn)(STUDENT *, void *)){
    struct list_head *cur;
    STUDENT *stu;
    __list_for_each(cur, &cls->student_list) {
        stu = list_entry(cur, STUDENT, node);
        each_do_fn(stu, env);
    }
}

typedef int cmp_fn(const void *, const STUDENT *);

static STUDENT *_class_find_student(CLASS *cls, const void *key, cmp_fn *cmp){
    struct list_head *cur;
    STUDENT *stu;
    __list_for_each(cur, &cls->student_list) {
        stu = list_entry(cur, STUDENT, node);
        if(cmp(key, stu) == 0)
            return stu;
    }
    return NULL;
}

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

static void _student_display(STUDENT *stu, void *env){
    int *indent = env;
    student_display(stu, *indent + 2);
}

void class_display(CLASS *cls, int indent){
    char format[] = "%0sCLASS: [name]%s\n";
    format[1] = '0' + indent;
    printf(format, "", cls->name);
    class_each_student(cls, &indent, _student_display);
}
