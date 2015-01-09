#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "class.h"
#include "grade.h"
#include "event.h"



#define TEST_DRIVER(fun)\
    printf("----------------\n%s:\n", #fun);\
    fun();


CLASS *prepare_class(char *cls_name){
    CLASS *cls = class_new(cls_name);
    STUDENT *stu = student_new(1, "zyx", 98);
    class_add_student(cls, stu);
    stu = student_new(18, "abc", 88);
    class_add_student(cls, stu);
    stu = student_new(34, "ttt", 78);
    class_add_student(cls, stu);
    stu = student_new(35, "one", 78);
    class_add_student(cls, stu);
    stu = student_new(23, "ry", 85);
    class_add_student(cls, stu);
    return cls;
}

void test_class_dislpay(){
    CLASS *cls = prepare_class("A01");
    class_display(cls, 0);
    class_free(cls);
}

void test_class_find(){
    CLASS *cls = prepare_class("A01");
    student_display(class_find_student_by_id(cls, 18), 0);
    student_display(class_find_student_by_name(cls, "zyx"), 0);
    class_free(cls);
}

void test_class_del(){
    CLASS *cls = prepare_class("A01");
    STUDENT *stu = class_find_student_by_name(cls, "zyx");
    class_del_student(cls, stu);
    class_display(cls, 0);
    class_free(cls);
}

void test_class_sort(){
    CLASS *cls = prepare_class("A01");
    STUDENT **arr = class_sort_by_score(cls);
    students_display(arr, cls->stu_count);

    class_free(cls);
    free(arr);
}


void test_class_save(){
    CLASS *cls = prepare_class("A01");
    FILE *fp = fopen("class.data", "w");
    class_save(cls, fp);
    fclose(fp);
    class_free(cls);
}

void test_class_load(){
    FILE *fp = fopen("class.data", "r");
    CLASS *cls = class_load(fp);
    fclose(fp);
    class_display(cls, 0);
    class_free(cls);
}

GRADE *prepare_grade(int year){
    GRADE *grade = grade_new(year);
    CLASS *cls = prepare_class("A01");
    grade_add_class(grade, cls);
    cls = prepare_class("A02");
    grade_add_class(grade, cls);
    cls = prepare_class("A03");
    grade_add_class(grade, cls);
    return grade;
}

void test_grade_display(){
    GRADE *grade = prepare_grade(1998);
    grade_display(grade, 0);
    grade_free(grade);
}

void test_grade_find(){
    GRADE *grade = prepare_grade(1998);
    CLASS *cls = grade_find_class_by_name(grade, "A02");
    class_display(cls, 0);
    grade_free(grade);
}

void test_grade_del(){
    GRADE *grade = prepare_grade(1998);
    CLASS *cls = grade_find_class_by_name(grade, "A02");
    grade_del_class(grade, cls);
    grade_display(grade, 0);
    grade_free(grade);
}

void test_grade_sort(){
    GRADE *grade = prepare_grade(1998);
    STUDENT **arr = grade_sort_by_score(grade);
    students_display(arr, grade->stu_count);
    grade_free(grade);
    free(arr);
}

void test_grade_save(){
    GRADE *grade = prepare_grade(1998);
    FILE *fp = fopen("grade.data", "w");
    grade_save(grade, fp);
    fclose(fp);
    grade_free(grade);
}

void test_grade_load(){
    FILE *fp = fopen("grade.data", "r");
    GRADE *grade = grade_load(fp);
    fclose(fp);
    grade_display(grade, 0);
    grade_free(grade);
}




static void _e_handler1(void *sender, void *receiver, void *arg){
    int *sender2 = sender;
    int *receiver2 = receiver;
    int *arg2 = arg;
    printf("_e_handler1 %d %d %d\n", *sender2, *receiver2, *arg2);
}

static void _e_handler2(void *sender, void *receiver, void *arg){
    int *sender2 = sender;
    int *receiver2 = receiver;
    int *arg2 = arg;
    printf("_e_handler2 %d %d %d\n", *sender2, *receiver2, *arg2);
}

void test_event(){
    int sender = 10;
    EVENT *e = event_new(&sender);
    int receiver = 100;
    event_add(e, &receiver, _e_handler1);
    event_add(e, &receiver, _e_handler2);

    int arg = 20;
    event_trigger(e, &arg);

    event_remove(e, &receiver, _e_handler1);
    arg = 30;
    event_trigger(e, &arg);

    event_free(e);
}


void test_class_event(){
    GRADE *grade = prepare_grade(1998);
    printf("%d\n", grade->stu_count);

    CLASS *cls = grade_find_class_by_name(grade, "A02");
    STUDENT *stu = student_new(2, "zyx2", 68);
    class_add_student(cls, stu);
    printf("%d\n", grade->stu_count);

    class_del_student(cls, stu);
    printf("%d\n", grade->stu_count);

    grade_free(grade);
}


void test_class_event_after_load(){
    FILE *fp = fopen("grade.data", "r");
    GRADE *grade = grade_load(fp);
    printf("%d\n", grade->stu_count);

    CLASS *cls = grade_find_class_by_name(grade, "A02");
    STUDENT *stu = student_new(2, "zyx2", 68);
    class_add_student(cls, stu);
    printf("%d\n", grade->stu_count);

    class_del_student(cls, stu);
    printf("%d\n", grade->stu_count);

    grade_free(grade);
}




int main(){

    TEST_DRIVER(test_class_dislpay);
    TEST_DRIVER(test_class_find);
    TEST_DRIVER(test_class_del);
    TEST_DRIVER(test_class_sort);
    TEST_DRIVER(test_class_save);
    TEST_DRIVER(test_class_load);

    TEST_DRIVER(test_grade_display);
    TEST_DRIVER(test_grade_find);
    TEST_DRIVER(test_grade_del);
    TEST_DRIVER(test_grade_sort);
    TEST_DRIVER(test_grade_save);
    TEST_DRIVER(test_grade_load);

    TEST_DRIVER(test_event);
    TEST_DRIVER(test_class_event);
    TEST_DRIVER(test_class_event_after_load);




    return 0;
}


// gcc event.c student.c class.c grade.c test.c -o test.out && ./test.out
// gcc test.c -E -o test.i
