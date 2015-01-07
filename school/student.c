#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "class.h"


STUDENT *student_new(int id, char *name, int score){
    STUDENT *stu = malloc(sizeof(*stu));
    stu->id = id;
    strncpy(stu->name, name, STU_NAMESIZE);
    stu->score = score;
    stu->cls = NULL;
    return stu;
}

void student_free(STUDENT *stu){
    free(stu);
}

//sort by score desc, class name asc, student id asc
int student_cmp_by_score(const STUDENT **stu1, const STUDENT **stu2){
    int diff = (*stu2)->score - (*stu1)->score;
    if(diff != 0) return diff;
    diff = strcmp((*stu1)->cls->name, (*stu2)->cls->name);
    if(diff != 0) return diff;
    return (*stu1)->id - (*stu2)->id;
}

STUDENT **student_sort(STUDENT **arr, STUDENT_CMP_FN *cmp, int length){
    qsort(arr, length, sizeof(STUDENT *), (int(*)(const void *, const void *))cmp);
    return arr;
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
    sprintf(format, "%%%dsSTUDENT: [class(name)]%%s\t[id]%%02d\t[name]%%s\t[score]%%2d\n", indent);
    printf(format, "", (stu->cls == NULL) ? "nil" : stu->cls->name, stu->id, stu->name, stu->score);
}

void students_display(STUDENT **stus, int length){
    int i;
    for(i = 0; i < length; i++)
        student_display(stus[i], 2);
}
