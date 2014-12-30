#include <stdio.h>
#include <stdlib.h>
#include "class.h"
#include "student.h"


void test_class(){
    CLASS *cls = class_new("A01");
    STUDENT *stu = student_new(1, "zyx", 98);
    class_add_student(cls, stu);
    stu = student_new(18, "abc", 88);
    class_add_student(cls, stu);
    stu = student_new(34, "ttt", 78);
    class_add_student(cls, stu);
    stu = student_new(23, "ry", 85);
    class_add_student(cls, stu);
    class_display(cls, 0);

    stu = class_find_student_by_id(cls, 18);
    printf("find: ");
    student_display(stu, 0);

    stu = class_find_student_by_name(cls, "zyx");
    printf("find: ");
    student_display(stu, 0);

    class_del_student(cls, stu);
    printf("del: \n");
    class_display(cls, 2);

    FILE *fp = fopen("class.data", "w");
    class_save(cls, fp);

    class_free(cls);
}

void test_class_load(){
    FILE *fp = fopen("class.data", "r");
    CLASS *cls = class_load(fp);

    class_display(cls, 0);
    class_free(cls);
}


int main(){
    test_class();
    test_class_load();

    return 0;
}


// gcc student.c class.c test.c -o test.out && ./test.out
