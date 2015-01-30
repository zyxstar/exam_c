#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


#define MAXTOKENS 100
#define MAXTOKENLEN 64

enum type_tag {IDENTIFIER, QUALIFIER, TYPE};

struct token{
    char type;
    char string[MAXTOKENLEN];
};

int top = -1;

struct token stack[MAXTOKENS];//在第一个标识符前保存所有的标记
struct token this;//保存刚读入的标记

#define pop stack[top--]
#define push(s) stack[++top] = s

enum type_tag
classify_string(void){//推断标识符的类型
    char *s = this.string;
    if(!strcmp(s, "const")){
        strcpy(s, "read-only");
        return QUALIFIER;
    }
    if(!strcmp(s, "volatile")) return QUALIFIER;
    if(!strcmp(s, "void")) return TYPE;
    if(!strcmp(s, "char")) return TYPE;
    if(!strcmp(s, "signed")) return TYPE;
    if(!strcmp(s, "unsigned")) return TYPE;
    if(!strcmp(s, "short")) return TYPE;
    if(!strcmp(s, "int")) return TYPE;
    if(!strcmp(s, "long")) return TYPE;
    if(!strcmp(s, "float")) return TYPE;
    if(!strcmp(s, "double")) return TYPE;
    if(!strcmp(s, "struct")) return TYPE;
    if(!strcmp(s, "union")) return TYPE;
    if(!strcmp(s, "enum")) return TYPE;

    return IDENTIFIER;
}


void
gettoken(void){//读取下一个标识到 this
    char *p = this.string;//存入位置

    while((*p = getchar()) == ' ');//略过所有空白

    if(isalnum(*p)){
        while(isalnum(*++p = getchar()));
        ungetc(*p, stdin);
        *p = '\0';
        this.type = classify_string();
        return;
    }

    if(*p == '*'){
        strcpy(this.string, "pointer to");
        this.type = '*';
        return ;
    }

    this.string[1] = '\0';
    this.type = *p;
    return;
}

//状态函数
void initialize(), get_array(), get_params(), get_lparen(), get_ptr_part(),
        get_type();

void (*nextstate)(void) = initialize;

int
main() {
    /* 在不同的状态间切换，直到指针值为NULL */
    while (nextstate != NULL)
        (*nextstate)();
    return 0;
}

void
initialize() {
    gettoken();
    while (this.type != IDENTIFIER) {
        push(this);
        gettoken();
    }
    printf("%s is ", this.string);
    gettoken();
    nextstate = get_array;
}

void
get_array() {
    nextstate = get_params;
    while (this.type == '[') {
        printf("array ");
        gettoken(); /* a number or ']' */
        if (isdigit(this.string[0])) {
            printf("0..%d ", atoi(this.string) - 1);
            gettoken(); /* read the ']' */
        }
        gettoken(); /* read next past the ']' */
        printf("of ");
        nextstate = get_lparen;
    }
}

void
get_params() {
    nextstate = get_lparen;
    if (this.type == '(') {
        while (this.type != ')') {
            gettoken();
        }
        gettoken();
        printf("function returning ");
    }
}

/* 左小括号 */
void
get_lparen() {
    nextstate = get_ptr_part;
    if (top >= 0) {
        if (stack[top].type == '(') {
            pop;
            gettoken(); /* read past ')' */
            nextstate = get_array;
        }
    }
}

void
get_ptr_part() {
    nextstate = get_type;
    if (stack[top].type == '*') {
        printf("pointer to ");
        pop;
        nextstate = get_lparen;
    } else if (stack[top].type == QUALIFIER) {
        printf("%s ", pop.string);
        nextstate = get_lparen;
    }
}

void
get_type() {
    nextstate = NULL;
    /* process tokens that we stacked while reading to
     identifier */
    while (top >= 0) {
        printf("%s ", pop.string);
    }
    printf("\n");
}

// int*(*foop[10])()
