#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

STUDENT *student_new(int id, char *name, int score){
    STUDENT *stu = malloc(sizeof(*stu));
    stu->id = id;
    strncpy(stu->name, name, STU_NAMESIZE);
    stu->score = score;
    return stu;
}

void student_free(STUDENT *stu){
    free(stu);
}

void student_save(STUDENT *stu, FILE *fp){
    fwrite(stu, sizeof(STUDENT), 1, fp);
}

STUDENT *student_load(FILE *fp){
    STUDENT *stu = malloc(sizeof(*stu));
    fread(stu, sizeof(STUDENT), 1, fp);
    return stu;
}

void student_display(STUDENT *stu, int indent){
    char format[256] = {0};
    sprintf(format, "%%%dsSTUDENT: [id]%%2d [name]%%s [score]%%2d\n", indent);
    printf(format, "", stu->id, stu->name, stu->score);
}
