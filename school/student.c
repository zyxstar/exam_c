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

void student_display(STUDENT *stu, int indent){
    char format[256] = {0};
    sprintf(format, "%%%dsSTUDENT: [id]%%2d [name]%%s [score]%%2d\n", indent);
    printf(format, "", stu->id, stu->name, stu->score);
}


char *get_filled_string(int len, int ch){
    char *str = malloc(sizeof(char) * (len + 1));
    memset(str, ch, len);
    str[len] = '\0';
    return str;
}

