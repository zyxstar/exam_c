#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kernel_list.h"
#include "class.h"
#include "student.h"


CLASS *class_new(char *name){
    CLASS *cls = malloc(sizeof(*cls));
    strncpy(cls->name, name, CLS_NAMESIZE);
    INIT_LIST_HEAD(&cls->student_list);
    return cls;
}

static void _student_free(STUDENT *stu, int idx, void *env){
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

void class_each_student(CLASS *cls, void *env, EACH_DO_FN *each_do){
    struct list_head *cur;
    STUDENT *stu;
    int i = 0;
    __list_for_each(cur, &cls->student_list) {
        stu = list_entry(cur, STUDENT, node);
        each_do(stu, i++, env);
    }
}

typedef int _CMP_FN(const void *, const STUDENT *);

static STUDENT *_class_find_student(CLASS *cls, const void *key, _CMP_FN *cmp){
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




static void _student_save(STUDENT *stu, int idx, void *env){
    FILE *fp = ((void**)env)[0];
    int *num = ((void**)env)[1];
    student_save(stu, fp);
    *num = idx;
}

void class_save(CLASS *cls, FILE *fp){
    long offset_count, offset_stream;
    fwrite(cls, sizeof(CLASS), 1, fp);
    offset_count = ftell(fp);//save `count` position
    int count;
    fseek(fp, sizeof(int), SEEK_CUR);//retain `count` memory

    void *env[] = {fp, &count};
    class_each_student(cls, env, _student_save);
    count += 1;
    offset_stream = ftell(fp);

    fseek(fp, offset_count, SEEK_SET);//go back to write `count`
    fwrite(&count, sizeof(count), 1, fp);

    fseek(fp, offset_stream, SEEK_SET);//reset offset stream
}

CLASS *class_load(FILE *fp){
    CLASS *cls = malloc(sizeof(CLASS));
    fread(cls, sizeof(CLASS), 1, fp);
    INIT_LIST_HEAD(&cls->student_list);
    int i, count;
    fread(&count, sizeof(int), 1, fp);
    for(i = 0; i < count; i++)
        class_add_student(cls, student_load(fp));
    return cls;
}


static void _student_display(STUDENT *stu, int idx, void *env){
    int *indent = env;
    student_display(stu, *indent + 2);
}

void class_display(CLASS *cls, int indent){
    char format[] = "%0sCLASS: [name]%s\n";
    format[1] = '0' + indent;
    printf(format, "", cls->name);
    class_each_student(cls, &indent, _student_display);
}
