#ifndef STUDENT_H_INCLUEDE
#define STUDENT_H_INCLUEDE

#include "list.h"

#define STU_NAMESIZE 32

typedef struct {
    int id;
    char name[STU_NAMESIZE];
    int score;
    struct list_head node;
} STUDENT;

STUDENT *student_new(int id, char *name, int score);
void student_free(STUDENT *stu);
void student_display(STUDENT *stu, int indent);

char *get_filled_string(int len, int ch);

#endif
