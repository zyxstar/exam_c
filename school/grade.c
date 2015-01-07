#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kernel_list.h"
#include "kernel_list_helper.h"
#include "class.h"
#include "grade.h"


GRADE *grade_new(int year){
    GRADE *grade = malloc(sizeof(*grade));
    INIT_LIST_HEAD(&grade->class_list);
    grade->year = year;
    grade->cls_count = 0;
    grade->stu_count = 0;
    return grade;
}

static void _class_free(CLASS *cls, int idx, void *env){
    class_free(cls);
}

void grade_free(GRADE *grade){
    grade_each_class(grade, NULL, _class_free);
    free(grade);
}


void grade_add_class(GRADE *grade, CLASS *cls){
    list_add_tail(&cls->node, &grade->class_list);
    cls->grade = grade;
    grade->cls_count++;
    grade->stu_count += cls->stu_count;
}

void grade_del_class(GRADE *grade, CLASS *cls){
    __list_del_entry(&cls->node);
    grade->stu_count -= cls->stu_count;
    grade->cls_count--;
    class_free(cls);
}

// declare
void grade_each_class(GRADE *, void *env, void(*each_do)(CLASS *, int idx, void *env));
// implement
_implement_list_each(grade_each_class, GRADE, class_list, CLASS, node);




// declare
CLASS *_grade_find_class(GRADE *, const void *key, int(*cmp)(const void *key, const CLASS *));
// implement
_implement_list_find(_grade_find_class, GRADE, class_list, CLASS, node);

static _name_cmp(const void *key, const CLASS *cls){
    const char *name = key;
    return strcmp(cls->name, name);
}

CLASS *grade_find_class_by_name(GRADE *grade, const char *name){
    return _grade_find_class(grade, name, _name_cmp);
}






static void _append_stu_to_arr(STUDENT *stu, int _, void *env){
    STUDENT **arr = ((void **)env)[0];
    int *idx = ((void **)env)[1];
    arr[(*idx)++] = stu;
}

static void _append_cls_to_arr(CLASS *cls, int _, void *env){
    class_each_student(cls, env, _append_stu_to_arr);
}

STUDENT ** grade_sort_by_score(GRADE *grade){
    STUDENT **arr = malloc(sizeof(STUDENT *) * grade->stu_count);
    int idx = 0;
    void *env[] = {arr, &idx};
    grade_each_class(grade, env, _append_cls_to_arr);
    return student_sort(arr, student_cmp_by_score, grade->stu_count);
}






// declare
void _grade_save(GRADE *, FILE *, void(*save_entry)(CLASS *, FILE *));
// implement
_implement_list_save(_grade_save, GRADE, class_list, CLASS, node);

void grade_save(GRADE *grade, FILE *fp){
    grade->cls_count = 0; // need'nt write to file
    grade->stu_count = 0;
    _grade_save(grade, fp, class_save);
}




// declare
GRADE *_grade_load(FILE *, void(*load_entry)(GRADE *, FILE *));
// implement
_implement_list_load(_grade_load, GRADE, class_list);

static void _class_load_to_grade(GRADE *grade, FILE *fp){
    grade_add_class(grade, class_load(fp));
}

GRADE *grade_load(FILE *fp){
    return _grade_load(fp, _class_load_to_grade);
}


static void _class_display(CLASS *cls, int idx, void *env){
    int *indent = env;
    class_display(cls, *indent + 2);
}

void grade_display(GRADE *grade, int indent){
    char format[] = "%0sGRADE: [year]%d\t[cls_count]%d\t[stu_count]%d\n";
    format[1] = '0' + (indent > 9 ? 9 : indent);
    printf(format, "", grade->year, grade->cls_count, grade->stu_count);
    grade_each_class(grade, &indent, _class_display);
}




