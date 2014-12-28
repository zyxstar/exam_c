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

    class_free(cls);

}


int main(){

    test_class();

    return 0;
}


// gcc student.c class.c test.c -o test.out && ./test.out
