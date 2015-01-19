#ifndef STUDENT_H_INCLUEDE
#define STUDENT_H_INCLUEDE

#include <stdio.h>
#include <kernel_list.h>

#define STU_NAMESIZE 32

typedef struct CLASS_TAG CLASS;

typedef struct {
    int id;
    char name[STU_NAMESIZE];
    int score;
    struct list_head node;
    CLASS *cls;
} STUDENT;


typedef int STUDENT_CMP_FN(const STUDENT **, const STUDENT **);





STUDENT *student_new(int id, char *name, int score);
void student_free(STUDENT *stu);


//sort by score desc, class name asc, student id asc
int student_cmp_by_score(const STUDENT **, const STUDENT **);
STUDENT **student_sort(STUDENT **, STUDENT_CMP_FN *, int length);


void student_save(STUDENT *stu, FILE *fp);
STUDENT *student_load(FILE *fp);

void student_display(STUDENT *stu, int indent);

void students_display(STUDENT **stus, int length);
#endif
