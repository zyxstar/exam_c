#include "list.h"
#include "student.h"

#define CLS_NAMESIZE 32

typedef struct {
    char name[CLS_NAMESIZE];
    struct list_head student_list;
} CLASS;
